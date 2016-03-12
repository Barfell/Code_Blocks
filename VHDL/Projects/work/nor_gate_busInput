LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY nor_gate_busInput IS
    GENERIC(size: INTEGER);
    PORT(a:IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
  	 b:IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
    	 q:OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
END nor_gate_busInput;

ARCHITECTURE behave OF nor_gate_busInput IS
BEGIN
  q<=a NOR b;
END behave;