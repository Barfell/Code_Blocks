LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY tb_full_adder IS END tb_full_adder;

ARCHITECTURE test OF tb_full_adder IS
COMPONENT full_adder IS
        PORT(a, b, carry_in: IN STD_LOGIC;
            carry_out, sum: OUT STD_LOGIC);
END COMPONENT;

SIGNAL test_vector: STD_LOGIC_VECTOR(2 downto 0);
SIGNAL result, cout: STD_LOGIC;
BEGIN
  T1: full_adder PORT MAP(a=>test_vector(2), b=>test_vector(1), carry_in=>test_vector(0), carry_out=>cout, sum=>result);
    test_vector<="000",
                 "001" AFTER 10 ns,
                 "010" AFTER 20 ns,
		 "011" AFTER 30 ns,
                 "100" AFTER 40 ns,
		 "101" AFTER 50 ns,
                 "110" AFTER 60 ns,
                 "111" AFTER 70 ns;
END test;