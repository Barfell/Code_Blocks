LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions
USE IEEE.std_logic_signed.all;   --math operations for signed std_logic

ENTITY counter_up_down_4bit IS
    PORT(up, clk, reset: IN STD_LOGIC;
        out1: OUT STD_LOGIC;
        out2: OUT STD_LOGIC_VECTOR(3 DOWNTO 0));
END counter_up_down_4bit;

ARCHITECTURE behave OF counter_up_down_4bit IS
SIGNAL count : STD_LOGIC_VECTOR(3 DOWNTO 0);

BEGIN
PROCESS (clk, reset)
BEGIN
    IF reset='0' THEN                  --asynchronous active low reset
        count<=(OTHERS=>'0');
    ELSIF rising_edge(clk) THEN
        CASE up IS
        WHEN '1'=>
	    count<=count+1;
        WHEN OTHERS=>
	    count<=count-1;
        END CASE;
	
	IF ((count=15 AND up='1') OR (count=0 AND up='0')) THEN
	    out1<='1';
	ELSE
	    out1<='0';
	END IF;
	out2<=count;
    END IF;
END PROCESS;
END behave; -- Arch_counter_sig