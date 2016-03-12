-- Package: Semaphores

package Semaphores is
   protected type CountingSemaphore(Max: Natural; Initial: Natural)  is
      entry Wait;
      entry Signal;
   private
      Count : Natural := Initial;    --number of keys available
      MaxCount : Natural := Max;   --total number of keys
   end CountingSemaphore;
end Semaphores;

