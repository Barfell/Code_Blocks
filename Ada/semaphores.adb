-- Package: Semaphores
with Ada.Text_IO;
use Ada.Text_IO;


package body Semaphores is
   protected body CountingSemaphore is
      entry Wait -- SemPend()
         when count>0 is          --wait for keys
            begin
                count:=count-1;
      end Wait;
      
      entry Signal -- SemPost()
          when count<MaxCount is       --can't post if all keys are available
             begin
                count:=count+1;
      end Signal;
      
   end CountingSemaphore;
end Semaphores;


