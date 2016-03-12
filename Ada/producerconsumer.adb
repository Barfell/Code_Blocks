with Ada.Text_IO;
use Ada.Text_IO;

with Ada.Real_Time;
use Ada.Real_Time;

with Ada.Numerics.Discrete_Random;

with semaphores;
use semaphores;

procedure ProducerConsumer is

   X : Integer; -- Shared Variable
   N : constant Integer := 40; -- Number of produced and comsumed variables

   pragma Volatile(X); -- For a volatile object all reads and updates of
                       -- the object as a whole are performed directly
                       -- to memory (Ada Reference Manual, C.6)

   -- Random Delays
   subtype Delay_Interval is Integer range 50..250;
   package Random_Delay is new Ada.Numerics.Discrete_Random (Delay_Interval);
   use Random_Delay;
   G : Generator;

   SemWrite : CountingSemaphore(1, 1);               --semaphore for producer
   SemRead: CountingSemaphore(1, 0);                 --semaphore for consumer
   task Producer;
   task Consumer;

   task body Producer is
      Next : Time;
   begin
      Next := Clock;
      for I in 1..N loop
         -- Write to X
         SemWrite.Wait;         --SemPend()
         X := I;
         -- Next 'Release' in 50..250ms
         Next := Next + Milliseconds(Random(G));
         SemRead.Signal;        --SemPost()
         delay until Next;
      end loop;
   end;

   task body Consumer is
   begin
      for I in 1..N loop
         -- Read from X
         SemRead.Wait;         --SemPend()
         Put_Line(Integer'Image(X));
         SemWrite.Signal;      --SemPost()
      end loop;
   end;

begin -- main task
   null;
end ProducerConsumer;


