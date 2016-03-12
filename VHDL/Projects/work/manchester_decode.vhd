LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY manchester_decode IS
PORT(input: IN STD_LOGIC;
    output: OUT STD_LOGIC:='0');
END manchester_decode;

ARCHITECTURE behave OF manchester_decode IS
TYPE state_type IS (S0, S1, S2);     --for FSM use
SIGNAL state_mc: state_type:=S0;
BEGIN
PROCESS(input)
BEGIN
    CASE state_mc IS

        WHEN S0=>
	    IF (input='1') THEN        --maybe 10
	        state_mc<=S1;
	    ELSE                     --maybe 01
		state_mc<=S2;
	    END IF;

	WHEN S1=>
	    IF (input='0') THEN        --confirmed 10
		output<='1'; 
	    ELSE                      --confirmed 11
	        output<='0';
	    END IF;
	    state_mc<=S0;

	WHEN S2=>
	    output<='0';             --output is 0 whether we get 00 or 01
	    state_mc<=S0;

	WHEN OTHERS=>
	    state_mc<=S0;
	    output<='0';
    END CASE;
END PROCESS;
END behave;