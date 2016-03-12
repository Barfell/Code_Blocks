USE work.opc_pack.all;

ENTITY tb_operator_overloading IS END tb_operator_overloading;

ARCHITECTURE test OF tb_operator_overloading IS
COMPONENT operator_overloading IS
PORT(a, b: IN opc;
    q: OUT opc);
END COMPONENT;
SIGNAL a, b, q: opc;

BEGIN
T1: operator_overloading PORT MAP(a, b, q);
a<='X',
   '1' AFTER 10 ns,
   '0' AFTER 20 ns,
   'H' AFTER 30 ns,
   'Z' AFTER 40 ns;
b<='X',
   '1' AFTER 5 ns,
   '0' AFTER 10 ns,
   'H' AFTER 15 ns,
   'Z' AFTER 20 ns,
   'X' AFTER 25 ns,
   '1' AFTER 30 ns,
   '0' AFTER 35 ns,
   'H' AFTER 40 ns;
END test;