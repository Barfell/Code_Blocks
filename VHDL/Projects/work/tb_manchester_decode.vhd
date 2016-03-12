LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY tb_manchester_decode IS END tb_manchester_decode;

ARCHITECTURE test OF tb_manchester_decode IS
COMPONENT manchester_decode IS
PORT(input: IN STD_LOGIC;
    output: OUT STD_LOGIC:='0');
END COMPONENT;

SIGNAL input: STD_LOGIC:='0';
SIGNAL output: STD_LOGIC;

BEGIN
T1: manchester_decode PORT MAP(input, output);
input<='0',
       '1' AFTER 5 ns,
       '0' AFTER 10 ns,
       '1' AFTER 15 ns,
       '1' AFTER 20 ns,
       '0' AFTER 25 ns,
       '1' AFTER 30 ns,
       '0' AFTER 35 ns;

END test;