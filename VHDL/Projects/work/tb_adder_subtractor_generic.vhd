-- A-B=A+B'+1
LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY tb_add_subb IS END tb_add_subb;

ARCHITECTURE test OF tb_add_subb IS
CONSTANT size : INTEGER:=4;          --4-bit adder subtractor
   COMPONENT add_subb
	  GENERIC(size: INTEGER);
          PORT(a, b: IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);  --std_logic_vector defines array of 8 elements with indexed from 0 to 7; can use bit_vector as well
              add_sub: IN STD_LOGIC;
              cout: OUT STD_LOGIC;
              sum: OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
   END COMPONENT;
  
   SIGNAL a, b, sum: STD_LOGIC_VECTOR(size-1 DOWNTO 0);
   SIGNAL add_sub, cout: STD_LOGIC;
   
BEGIN

  T1:add_subb GENERIC MAP (size) PORT MAP (a, b, add_sub, cout, sum);
  
  a <="0000",
    "1111" AFTER 10 ns,
    "1001" AFTER 20 ns,
    "1010" AFTER 30 ns,
    "1011" AFTER 40 ns,
    "1100" AFTER 50 ns, 
    "1101" AFTER 60 ns,
    "1110" AFTER 70 ns,
    "0001" AFTER 80 ns;
       
  b <="0000",
    "0111" AFTER 10 ns,
    "0001" AFTER 20 ns,
    "0010" AFTER 30 ns,
    "0011" AFTER 40 ns,
    "0100" AFTER 50 ns, 
    "0101" AFTER 60 ns,
    "0110" AFTER 70 ns,
    "0111" AFTER 80 ns;

       
   add_sub <= '0',
          '1' AFTER 50 ns;

END test;