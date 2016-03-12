LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY nand_gate IS
  PORT(a, b:IN STD_LOGIC;
    	q:OUT STD_LOGIC);
END nand_gate;

ARCHITECTURE behave OF nand_gate IS
BEGIN
  q<=a NAND b;
END behave;