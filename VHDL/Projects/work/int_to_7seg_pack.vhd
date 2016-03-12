LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

PACKAGE int_to_7seg_pack IS

TYPE logic_vector_array IS ARRAY (0 TO 9) OF STD_LOGIC_VECTOR (7 DOWNTO 0);

END PACKAGE int_to_7seg_pack;

PACKAGE BODY int_to_7seg_pack IS

PROCEDURE int_to_bcd(SIGNAL int_val : IN INTEGER; SIGNAL bcd2, bcd1, bcd0: OUT INTEGER) IS
VARIABLE temp: INTEGER:=int_val;
BEGIN
    bcd0<=temp MOD 10;
    temp:=temp/10;
    bcd1<=temp MOD 10;
    bcd2<=temp/10;
END int_to_bcd;

END int_to_7seg_pack;