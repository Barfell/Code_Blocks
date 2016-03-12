LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions
USE IEEE.std_logic_signed.all;   --math operations for signed std_logic

ENTITY tb_frequency_divider_generic IS END tb_frequency_divider_generic;

ARCHITECTURE test of tb_frequency_divider_generic IS
COMPONENT frequency_divider_generic IS
    GENERIC(divide_by: INTEGER);
    PORT(clk_in, reset: IN STD_LOGIC;
        output: OUT STD_LOGIC);
END COMPONENT;

SIGNAL reset: STD_LOGIC:='0';
SIGNAL clk_in: STD_LOGIC:='0';
SIGNAL output: STD_LOGIC;

BEGIN
T1: frequency_divider_generic GENERIC MAP(16) PORT MAP(clk_in, reset, output);

clk_in<=NOT(clk_in) AFTER 5 ns;
reset<='1' AFTER 100 ns;
END test;