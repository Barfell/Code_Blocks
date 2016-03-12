LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions
USE IEEE.std_logic_signed.all;   --math operations for signed std_logic

ENTITY frequency_divider_generic IS
    GENERIC(divide_by: INTEGER);
    PORT(clk_in, reset: IN STD_LOGIC;
        output: OUT STD_LOGIC);
END frequency_divider_generic;

ARCHITECTURE behave OF frequency_divider_generic IS
SIGNAL count: INTEGER RANGE 0 TO divide_by:=0;
BEGIN

PROCESS(clk_in, reset)
BEGIN
    If reset='0' THEN     --asynchronous, active low reset
	output<='0';
	count<=0;
    ELSIF rising_edge(clk_in) THEN
	count<=count+1;
        IF (count=divide_by-1) THEN
	    output<='1';
	    count<=0;
        ELSE
	    output<='0';
        END IF;
    END IF;
END PROCESS;
END behave;