LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY d_ff IS
PORT(d, clk: IN STD_LOGIC;
    q: OUT STD_LOGIC);
END d_ff;

ARCHITECTURE behave OF d_ff IS
BEGIN

PROCESS(clk)
BEGIN
    IF (rising_edge(clk)) THEN
	 q<=d;
    END IF;
END PROCESS;
END behave;