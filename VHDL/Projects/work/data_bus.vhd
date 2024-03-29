LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY data_bus IS
PORT(data_in: IN STD_LOGIC_VECTOR(3 DOWNTO 0);        --data bus
    data_out: OUT STD_LOGIC_VECTOR(3 DOWNTO 0):="ZZZZ";
    en0, en1, rd_wr0, rd_wr1, clk, rst: IN STD_LOGIC);                     --register read-write select, clock, register select
END data_bus;

ARCHITECTURE behave of data_bus IS

COMPONENT register_generic IS
GENERIC(size: INTEGER);
PORT(d: IN STD_LOGIC_VECTOR(size-1 DOWNTO 0); 
    clk, rst: IN STD_LOGIC;
    q: OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
END COMPONENT;

SIGNAL d0, d1, q0, q1: STD_LOGIC_VECTOR(3 DOWNTO 0);    --register internal outputs and inputs

BEGIN
R0: register_generic GENERIC MAP(4) PORT MAP (d0, clk, rst, q0);
R1: register_generic GENERIC MAP(4) PORT MAP (d1, clk, rst, q1);

data_out<=q0 WHEN en0='1' AND rd_wr0='0' else others=>'Z';
data_out<=q1 WHEN en1='1' AND rd_wr1='0' else others=>'Z';

d0<=data_in WHEN en0='1' AND rd_wr0='1';
d1<=data_in WHEN en1='1' AND rd_wr1='1';

END behave;