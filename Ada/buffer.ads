package Buffer is
   N: constant Integer := 4;           --4 element buffer
   subtype Item is Integer;
   type Index is mod N;
   type Item_Array is array(Index) of Item;

   protected type CircularBuffer is
      entry WriteBuf(X: in INTEGER);
      entry ReadBuf(Y: out INTEGER);
      
   private
      A: Item_Array;             --buffer array
      In_Ptr, Out_Ptr: Index := 0;
      Count: Integer range 0..N := 0;
      flag: Integer := 0;
   end CircularBuffer;
end Buffer;


