USE work.opc_pack.all;

ENTITY operator_overloading IS
PORT(a, b: IN opc;
    q: OUT opc);
END operator_overloading;

ARCHITECTURE behave OF operator_overloading IS
BEGIN
q<=a xor b;
END behave;