LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions
USE IEEE.std_logic_signed.all;   --math operations for signed std_logic

ENTITY tb_counter_up_down_4bit IS END tb_counter_up_down_4bit;

ARCHITECTURE test OF tb_counter_up_down_4bit IS
COMPONENT counter_up_down_4bit IS
    PORT(up, clk, reset : IN STD_LOGIC;
        out1: OUT STD_LOGIC;
        out2: OUT STD_LOGIC_VECTOR(3 DOWNTO 0));
END COMPONENT;

SIGNAL up: STD_LOGIC;
SIGNAL reset: STD_LOGIC:='0';
SIGNAL clk: STD_LOGIC:='0';
SIGNAL out1: STD_LOGIC:='0';
SIGNAL out2: STD_LOGIC_VECTOR(3 DOWNTO 0):=(OTHERS=>'0');

BEGIN
T1: counter_up_down_4bit PORT MAP(up, clk, reset, out1, out2);
reset<='1' AFTER 125 ns;
clk<=NOT(clk) AFTER 50 ns;
up<='1',
    '0' AFTER 945 ns,
    '1' AFTER 1845 ns,
    '0' AFTER 2025 ns;
END test;
