LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY tb_nand_gate IS END tb_nand_gate;

ARCHITECTURE test OF tb_nand_gate IS
COMPONENT nand_gate IS
  PORT (a:IN STD_LOGIC;
  	b:IN STD_LOGIC;
    	q:OUT STD_LOGIC);
END COMPONENT;

SIGNAL test_vector: STD_LOGIC_VECTOR(1 downto 0);
SIGNAL result: STD_LOGIC;
BEGIN
  T1: nand_gate PORT MAP(a=>test_vector(1), b=>test_vector(0), q=>result);
    test_vector<="00",
                 "01" AFTER 10 ns,
                 "10" AFTER 20 ns,
                 "11" AFTER 30 ns;
END test;