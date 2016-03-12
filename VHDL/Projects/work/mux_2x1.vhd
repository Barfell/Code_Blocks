LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY mux_2x1 IS
    PORT(a, b, ctrl: IN STD_LOGIC;
	q: OUT STD_LOGIC);
END mux_2x1;

ARCHITECTURE dataflow OF mux_2x1 IS
    BEGIN
	q<=a when ctrl='0' else b;
END dataflow;