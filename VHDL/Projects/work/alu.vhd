LIBRARY IEEE; -- These lines informs the compiler that the library IEEE is used
USE IEEE.std_logic_1164.all; -- contains the definition for the std_logic type plus some useful conversion functions

ENTITY alu IS
    GENERIC (size: INTEGER);
    PORT(a, b: IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
    	ctrl: IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    	q: OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0);
    	cout:OUT STD_LOGIC);
END alu;

architecture structural OF alu IS
--define building blocks of the ALU
COMPONENT nand_gate_busInput IS
    GENERIC(size: INTEGER);
    PORT (a:IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
  	  b:IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
    	  q:OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
END COMPONENT;

COMPONENT nor_gate_busInput IS
    GENERIC(size: INTEGER);
    PORT(a:IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
  	 b:IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
    	 q:OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
END COMPONENT;

COMPONENT add_subb IS
    GENERIC(size: INTEGER);
    PORT(a, b: IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);  --std_logic_vector defines array of 8 elements with indexed from 0 to 7; can use bit_vector as well
        add_sub: IN STD_LOGIC;
        cout: OUT STD_LOGIC;
        sum: OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
END COMPONENT;

COMPONENT mux_2x1_busInput IS
    GENERIC(size: INTEGER);
    PORT(a, b: IN STD_LOGIC_VECTOR(size-1 DOWNTO 0);
	ctrl: IN STD_LOGIC;
	q: OUT STD_LOGIC_VECTOR(size-1 DOWNTO 0));
END COMPONENT;

--define internal signals
SIGNAL i1, i2: STD_LOGIC_VECTOR(size-1 DOWNTO 0);   --input signals
SIGNAL nand_result, nor_result, add_sub_result: STD_LOGIC_VECTOR(size-1 DOWNTO 0); --output of each block
SIGNAL carry: STD_LOGIC; --ALU cout
SIGNAL add_sub_select: STD_LOGIC; --addition subtraction selector
SIGNAL address: STD_LOGIC_VECTOR(1 DOWNTO 0); --ALU mux selector
SIGNAL mux1_out, mux2_out, mux3_out: STD_LOGIC_VECTOR(size-1 DOWNTO 0);    --mux outputs

BEGIN
    --define internal signal connections with I/O ports
    i1<=a;
    i2<=b;
    cout<=carry;
    address(1)<=ctrl(1);
    address(0)<=ctrl(0);
    add_sub_select<=NOT(address(1)) AND address(0);
    q<=mux3_out;
    --connect the blocks
    NAND_UNIT: nand_gate_busInput GENERIC MAP(size) PORT MAP(a=>i1, b=>i2, q=>nand_result);

    NOR_UNIT: nor_gate_busInput GENERIC MAP(size) PORT MAP(a=>i1, b=>i2, q=>nor_result);

    ADD_SUB_UNIT: add_subb GENERIC MAP(size) PORT MAP(a=>i1, b=>i2, add_sub=>add_sub_select, cout=>carry, sum=>add_sub_result);

    MUX1: mux_2x1_busInput GENERIC MAP(size) PORT MAP(a=>add_sub_result, b=>add_sub_result, ctrl=>address(0), q=>mux1_out);

    MUX2: mux_2x1_busInput GENERIC MAP(size) PORT MAP(a=>nand_result, b=>nor_result, ctrl=>address(0), q=>mux2_out);

    MUX3: mux_2x1_busInput GENERIC MAP(size) PORT MAP(a=>mux1_out, b=>mux2_out, ctrl=>address(1), q=>mux3_out);
end structural;