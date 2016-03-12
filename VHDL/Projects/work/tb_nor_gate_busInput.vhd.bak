LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY tb_nand_gate_busInput IS END tb_nand_gate_busInput;

ARCHITECTURE test OF tb_nand_gate_busInput IS
CONSTANT size: INTEGER:=4;
COMPONENT nand_gate_busInput IS
  GENERIC(size: INTEGER);
  PORT (a:IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
  	b:IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
    	q:OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
END COMPONENT;

SIGNAL test_vector1, test_vector2: STD_LOGIC_VECTOR(size-1 DOWNTO 0);
SIGNAL result: STD_LOGIC_VECTOR(size-1 DOWNTO 0);

BEGIN
  T1: nand_gate_busInput GENERIC MAP(size) PORT MAP(a=>test_vector1, b=>test_vector2, q=>result);
    test_vector1<="0000",
                  "0001" AFTER 10 ns,
                  "0010" AFTER 20 ns,
                  "0011" AFTER 30 ns;
    test_vector2<="1111",
                  "1000" AFTER 10 ns,
                  "1100" AFTER 20 ns,
                  "1010" AFTER 30 ns;
END test;