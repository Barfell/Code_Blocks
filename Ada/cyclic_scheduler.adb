with Ada.Text_IO;
use Ada.Text_IO;

with Ada.Real_Time;
use Ada.Real_Time;

with System_Function_Package;
use System_Function_Package;

procedure Cyclic_Scheduler is
   X : Integer := 0; -- Input
   Y : Integer := 0; -- Input

   task Source_X;
   task Source_Y;
   task Scheduler;

   task body Source_X is -- Generates Data for Input X
      Start : Time;
      Next_Release : Time;
      Release : Time_Span := Milliseconds(0);
      Period : Time_Span := Milliseconds(1000);
   begin
      Start := Clock;
      Next_Release := Start + Release;
      loop
         delay until Next_Release;
         Next_Release:= Next_Release + Period;
         X := X + 1;
      end loop;
   end Source_X;

   task body Source_Y is -- Generated Data for Input Y
      Start : Time;
      Next_Release : Time;
      Release: Time_Span := Milliseconds(500);
      Period : Time_Span := Milliseconds(1000);
   begin
      Start := Clock;
      Next_Release := Start + Release;
      loop
         delay until Next_Release;
         Next_Release:= Next_Release + Period;
         Y := Y + 1;
      end loop;
   end Source_Y;

   task body Scheduler is
      A: Integer;
      B: Integer;
      Z : Integer; -- Output
    begin
      loop
         delay To_Duration(Milliseconds(100));        --wait 100ms
         A := System_A(X);                --process X
         
         Put_Line("A:");
         Put_Line(Integer'Image(A));
         
         delay To_Duration(Milliseconds(400));        --wait 400ms
         B := System_B(Y);                 --process Y
         
         Put_Line("B:");
         Put_Line(Integer'Image(B));
         
         Z:= System_C(A, B);                --calc Z
         
         Put_Line("Z:");           --display Z
         Put_Line(Integer'Image(Z));
         end loop;
   end Scheduler;

begin
   null;
end Cyclic_Scheduler;


