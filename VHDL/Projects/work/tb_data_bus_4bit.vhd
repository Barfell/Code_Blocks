LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY tb_data_bus_4bit IS END tb_data_bus_4bit;

ARCHITECTURE test of tb_data_bus_4bit IS
COMPONENT data_bus_4bit IS
PORT(data_bus: INOUT STD_LOGIC_VECTOR(3 DOWNTO 0):="ZZZZ";        --data bus
     rd_wr, clk, addr: IN STD_LOGIC);                     --register read-write select, clock, register select
END COMPONENT;

SIGNAL data_bus: STD_LOGIC_VECTOR(3 DOWNTO 0);
SIGNAL clk: STD_LOGIC:='0';
SIGNAL rd_wr, addr: STD_LOGIC;

BEGIN
T1: data_bus_4bit PORT MAP(data_bus, rd_wr, clk, addr);

data_bus<="0011",
          "1010" AFTER 10 ns;

rd_wr<='1',
       '0' AFTER 20 ns;

addr<='0',
      '1' AFTER 10 ns,
      '0' AFTER 20 ns,
      '1' AFTER 30 ns;


clk<=NOT(clk) AFTER 5 ns;
END test;