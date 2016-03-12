LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY manchester_encode IS
PORT(input, clk: IN STD_LOGIC;
    man_out: OUT STD_LOGIC);
END manchester_encode;

ARCHITECTURE behave OF manchester_encode IS
BEGIN
PROCESS(clk)
BEGIN
    man_out<=clk XOR input;
END PROCESS;
END behave;