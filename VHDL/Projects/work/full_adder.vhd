LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY full_adder IS
        PORT(a, b, carry_in: IN STD_LOGIC;
            carry_out, sum: OUT STD_LOGIC);
END full_adder;
    
--define architecture for full_adder
ARCHITECTURE dataflow OF full_adder IS
    BEGIN
        sum<=a xor b xor carry_in;
        carry_out<=(a and b) or (b and carry_in) or (a and carry_in);
END dataflow;