LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY tb_mux_2x1_busInput IS END tb_mux_2x1_busInput;

ARCHITECTURE test OF tb_mux_2x1_busInput IS
CONSTANT size: INTEGER:=4;
COMPONENT mux_2x1_busInput IS
    GENERIC(size: INTEGER);
    PORT(a, b: IN STD_LOGIC_VECTOR(size-1 downto 0);
	ctrl: IN STD_LOGIC;
	q: OUT STD_LOGIC_VECTOR(size-1 downto 0));
END COMPONENT;

SIGNAL i1: STD_LOGIC_VECTOR(size-1 DOWNTO 0):="0000";
SIGNAL i2: STD_LOGIC_VECTOR(size-1 DOWNTO 0):="1111";
SIGNAL result: STD_LOGIC_VECTOR(size-1 DOWNTO 0);
SIGNAL address: STD_LOGIC;
BEGIN
     T1: mux_2x1_busInput GENERIC MAP(size) PORT MAP(a=>i1, b=>i2, ctrl=>address, q=>result);
	address<='0',
	         '1' AFTER 20 ns;
	i1<="1010" AFTER 30 ns;
	i2<="0111" AFTER 30 ns;
END test;