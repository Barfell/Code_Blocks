LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY data_bus_4bit IS
PORT(data_bus: INOUT STD_LOGIC_VECTOR(3 DOWNTO 0):=(others=>'Z');        --data bus
     rd_wr, clk, addr: IN STD_LOGIC);                     --register read-write select, clock, register select
END data_bus_4bit;

ARCHITECTURE behave of data_bus_4bit IS

SIGNAL d0, d1, q0, q1: STD_LOGIC_VECTOR(3 DOWNTO 0);    --register internal outputs and inputs

BEGIN
PROCESS(clk)
BEGIN
    IF rising_edge(clk) THEN
	q1<=d1;
	q0<=d0;
    END IF;
END PROCESS;

data_bus<=q0 WHEN addr='0' AND rd_wr='0' ELSE "ZZZZ";
data_bus<=q1 WHEN addr='1' AND rd_wr='0' ELSE "ZZZZ";
d0<=data_bus WHEN addr='0' AND rd_wr='1';
d1<=data_bus WHEN addr='1' AND rd_wr='1';
END behave;