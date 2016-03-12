-- A-B=A+B'+1
LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

--define entity for adder-subtractor
ENTITY add_subb IS
    GENERIC(size: INTEGER);
    PORT(a, b: IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);  --std_logic_vector defines array of 8 elements with indexed from 0 to 7; can use bit_vector as well
        add_sub: IN STD_LOGIC;
        cout: OUT STD_LOGIC;
        sum: OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
END add_subb;

--define architecture for adder-subtractor
ARCHITECTURE structural OF add_subb IS
    COMPONENT full_adder                             --use a single full adder to build a bigger 8-bit adder-subtractor
        PORT(a, b, carry_in: IN STD_LOGIC;
            carry_out, sum: OUT STD_LOGIC);
    END COMPONENT;
    SIGNAL carry: STD_LOGIC_VECTOR(size DOWNTO 0);       --for connecting carry-out pins internally among adders
    SIGNAL b_bar: STD_LOGIC_VECTOR(size-1 DOWNTO 0);
    BEGIN
        carry(0)<=add_sub;
        cout<=add_sub XOR carry(size);
        G0: FOR i IN size-1 DOWNTO 0 GENERATE        --create the complete circuit
                b_bar(i)<=b(i) XOR carry(0);
                adder_subtractor_array: full_adder PORT MAP(a=>a(i), b=>b_bar(i), carry_in=>carry(i), carry_out=>carry(i+1), sum=>sum(i));
        END GENERATE G0;
END structural;