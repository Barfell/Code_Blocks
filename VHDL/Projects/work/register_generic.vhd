LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY register_generic IS
GENERIC(size: INTEGER);
PORT(d: IN STD_LOGIC_VECTOR(size-1 DOWNTO 0); 
    clk, rst: IN STD_LOGIC;
    q: OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
END register_generic;

ARCHITECTURE behave OF register_generic IS
SIGNAL q_int: STD_LOGIC_VECTOR(size-1 DOWNTO 0);
BEGIN

PROCESS(clk)
BEGIN
    IF (rising_edge(clk)) THEN
	 q_int<=d;
    END IF;
END PROCESS;

q<=q_int when rst='0' else (others=>'Z');          --asynchronous reset
END behave;