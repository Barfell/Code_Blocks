LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY mux_2x1_busInput IS
    GENERIC(size: INTEGER);
    PORT(a, b: IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
	ctrl: IN STD_LOGIC;
	q: OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
END mux_2x1_busInput;

ARCHITECTURE dataflow OF mux_2x1_busInput IS
    BEGIN
	q<=a when ctrl='0' else b;
END dataflow;