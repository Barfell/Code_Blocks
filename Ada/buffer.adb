with Ada.Text_IO;
use Ada.Text_IO;

package body Buffer is
    protected body CircularBuffer is
        entry WriteBuf(X: in INTEGER)          --write data to buffer
         when count<N is           --no writing to a full buffer
            begin
            A(In_Ptr):=X;
            In_Ptr:=In_Ptr+1;
            count:=count+1;
        end WriteBuf;
        
      entry ReadBuf(Y: out INTEGER)   --read data from buffer
         when count>0 is          --no reading from empty buffer
            begin
                Y:=A(Out_Ptr);
                if flag=0 then                --increment Out_Ptr only when both consumers have read the data
                  flag:=1;
                else
                  Out_Ptr:=Out_Ptr+1;
                  count:=count-1;
                  flag:=0;
                end if;
      end ReadBuf;
   end CircularBuffer;
end Buffer;
