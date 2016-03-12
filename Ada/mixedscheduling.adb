pragma Priority_Specific_Dispatching(FIFO_Within_Priorities, 2, 30);          --high priority tasks
pragma Priority_Specific_Dispatching(Round_Robin_Within_Priorities, 1, 1);    --low priority tasks

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;

procedure mixedscheduling is

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

   task type T(Period : Integer; ExecutionTime : Integer) is             --high priority tasks
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
   
   task type T_low(ID: Integer; ExecutionTime : Integer) is               --low priority tasks
      pragma Priority(1);
   end;
   
   task body T_low is
      Next : Time;
   begin
      Next := Start;
      loop
         Next := Next + Milliseconds(22); --loop takes about 23ms to finish
         --- Some dummy function
         Dummy := F(ExecutionTime);
         ---
         Duration_IO.Put(To_Duration(Clock - Start), 3, 3); -- print task execution duration
         Put(" : ");
         Int_IO.Put(ID, 2); -- print the priority
         Put_Line("");
         delay until Next; 
      end loop;
   end T_low;
   
   -- High priority tasks
   Task_1 : T(3, 1);
   Task_2 : T(4, 1);
   Task_3 : T(6, 1);
   
   -- Low priority tasks
   Task_4 : T_low(100, 1);
   Task_5 : T_low(101, 1);
   Task_6 : T_low(102, 1);
   
begin
   Start := Clock;
   null;
end mixedscheduling;
