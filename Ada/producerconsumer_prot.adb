with Ada.Text_IO;
use Ada.Text_IO;

with Ada.Real_Time;
use Ada.Real_Time;

with Buffer;
use Buffer;

with Ada.Numerics.Discrete_Random;

procedure ProducerConsumer_prot is

   N : constant Integer := 40; -- Number of produced and comsumed variables

   -- Random Delays
   subtype Delay_Interval is Integer range 50..250;
   package Random_Delay is new Ada.Numerics.Discrete_Random (Delay_Interval);
   use Random_Delay;
   G : Generator;
   
   data_box: CircularBuffer;     --use protected object
   
   task Producer;
   
   task body Producer is
      Next : Time;
   begin
      Next := Clock;
      for I in 1..N loop
         data_box.WriteBuf(I);    --write to buffer
         -- Next 'Release' in 50..250ms
         Next := Next + Milliseconds(Random(G));
         delay until Next;
      end loop;
   end;

   task type Consumer(ID: Integer);
   
   task body Consumer is
   X: INTEGER;
    begin
      for I in 1..N loop
         data_box.ReadBuf(X);        --read from buffer
         Put(Integer'Image(ID));     --display consumer ID
         Put("   ");
         Put_Line(Integer'Image(X));    --display data
      end loop;
   end;
   
   Consumer1: Consumer(1);
   Consumer2: Consumer(2);

begin -- main task
   null;
end ProducerConsumer_prot;



