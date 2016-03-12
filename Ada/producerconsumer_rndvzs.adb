with Ada.Text_IO;
use Ada.Text_IO;

with Ada.Real_Time;
use Ada.Real_Time;

with Ada.Numerics.Discrete_Random;

procedure ProducerConsumer_rndvzs is

   N : constant Integer := 40; -- Number of produced and comsumed variables

   -- Random Delays
   subtype Delay_Interval is Integer range 50..250;
   package Random_Delay is new Ada.Numerics.Discrete_Random (Delay_Interval);
   use Random_Delay;
   G : Generator;

   task Server is
       entry WriteBuf(X: in INTEGER);
       entry ReadBuf;
   end Server;
   task Producer;
   task Consumer;

   task body Producer is
      Next : Time;
   begin
      Next := Clock;
      for I in 1..N loop
         Server.WriteBuf(I);              --write data request
         -- Next 'Release' in 50..250ms
         Next := Next + Milliseconds(Random(G));
         delay until Next;
      end loop;
   end;

   task body Consumer is
   begin
      for I in 1..N loop
         Server.ReadBuf;           --read data request
      end loop;
   end;
   
   task body Server is
       N: constant Integer := 4;
       subtype Item is Integer;
       type Index is mod N;
       type Item_Array is array(Index) of Item;
       A: Item_Array;                        --circular buffer, 4 elements
       In_Ptr, Out_Ptr: Index := 0;
       Count: Integer range 0..N := 0;
   begin
      loop
          select
          when count<N =>             --no writing to full buffer
            accept WriteBuf(X: in INTEGER) do          --write buffer
                A(In_Ptr):=X;
                In_Ptr:=In_Ptr+1;
                count:=count+1;
            end WriteBuf;
            
          or
          
            when count>0 =>                  --no reading from empty buffer
                accept ReadBuf do             --read buffer
                    Put_Line(Integer'Image(A(Out_Ptr)));
                    Out_Ptr:=Out_Ptr+1;
                    count:=count-1;
                end ReadBuf;
            
           or
           
            terminate;                         --no more requests, terminate server task
           
           end select;
       end loop;
   end;

begin -- main task
   null;
end ProducerConsumer_rndvzs;


