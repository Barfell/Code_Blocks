LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY xorgate IS
PORT(a, b: IN STD_LOGIC;
    q: OUT STD_LOGIC);
END xorgate;

ARCHITECTURE behave OF xorgate IS
BEGIN
q<=a XOR b;
END behave;