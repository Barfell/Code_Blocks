pragma Task_Dispatching_Policy(FIFO_Within_Priorities);

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;

procedure overloaddetection is

   package Duration_IO is new Ada.Text_IO.Fixed_IO(Duration);
   package Int_IO is new Ada.Text_IO.Integer_IO(Integer);

--------

   function F(N : Integer) return Integer;

   function F(N : Integer) return Integer is
      X : Integer := 0;
   begin
      for Index in 1..N loop
         for I in 1..5000000 loop
            X := I;
         end loop;
      end loop;
      return X;
   end F;
   
--------   

   Start : Time;
   Dummy : Integer;

   task type T(Period : Integer; ExecutionTime : Integer) is
      pragma Priority(20 - Period); -- priority corresponds to period length
   end;

   task body T is
      Next : Time;
   begin
      Next := Start;
      loop
         Next := Next + Milliseconds(22*Period); --loop takes about 23ms to finish
         --- Some dummy function
         Dummy := F(ExecutionTime);
         ---
         Duration_IO.Put(To_Duration(Clock - Start), 3, 3); -- print task execution duration
         Put(" : ");
         Int_IO.Put(Period, 2); -- print the priority
         Put_Line("");
         delay until Next; 
      end loop;
   end T;

   task type WDT(Period : Integer) is
      pragma Priority(25);
      entry tick(isok: in Integer);
   end;
   
   task body WDT is                           --watchdog timer task
   Next : Time;
   ok : Integer;
   begin
      Next := Clock;
      ok := 1;
      loop
         select
            accept tick(isok : in Integer) do           --check for tick
               ok := 1;
            end tick;
            else
               Put_Line("OVERLOAD!!!!");
         end select;
         Next := Next + Milliseconds(Period*22);
         delay until Next; 
      end loop;
   end WDT;

   watchdog : WDT(36);          --36 for 4th task
   
   Task type D(Period : Integer) is             --overloaddetection task
      pragma Priority(1);
   end;
   
   task body D is
      Next : Time;
   begin
      Next := Start;
      loop
         Next := Next + Milliseconds(22*Period); -- period in multiple of 22ms
         watchdog.tick(1);                             --give task
         Duration_IO.Put(To_Duration(Clock - Start), 3, 3); -- print task execution duration
         Put(" : ");
         Int_IO.Put(12, 2); -- print ID=12
         Put_Line("");
         delay until Next; 
      end loop;
   end D;
   
   Detector: D(36);    --36 for 4th task
   
   -- Example Tasks
   Task_1 : T(3, 1);
   Task_2 : T(4, 1);
   Task_3 : T(6, 1);
   Task_4 : T(9, 2);

begin
   Start := Clock;
   null;
end overloaddetection;
