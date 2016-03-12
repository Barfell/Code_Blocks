USE work.opc_pack.all;

ENTITY opc_circuit IS
PORT(a, b: IN opc;
    q, qxor, qxnor: OUT opc);
END opc_circuit;

ARCHITECTURE behave of opc_circuit is
BEGIN
	q<=a;
	q<=b;
	qxor<=a xor b;
	qxnor<=a xnor b;
END behave;