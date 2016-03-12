pragma Task_Dispatching_Policy(FIFO_Within_Priorities);

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;

procedure rms is

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
      pragma Priority(20 - Period); -- priority corresponds to period length; needed since Ada doesn't support RMS out-of-the-box
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

   -- Example Tasks
   Task_1 : T(3, 1);
   Task_2 : T(4, 1);
   Task_3 : T(6, 1);

begin
   Start := Clock;
   null;
end rms;
