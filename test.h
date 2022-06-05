//RType
void addTest(int rd, int rs, int rt);
void subTest(int rd, int rs, int rt);
void andTest(int rd, int rs, int rt);
void orTest(int rd, int rs, int rt);
void xorTest(int rd, int rs, int rt);
void norTest(int rd, int rs, int rt);
void sltTest(int rd, int rs, int rt);
//J-Type
void jalTest(int address);
void jTest(int address);
void jrTest(int rs);
//branch
void beqTest(int rs, int rt, int imm);
void bneTest(int rs, int rt, int imm);
void bltzTest(int rs, int rt, int imm);
//IType
void addiTest(int rd, int rs, int imm);
void sltiTest(int rt, int rs, int imm);
void andiTest(int rt, int rs, int imm);
void oriTest(int rt, int rs, int imm);
void xoriTest(int rt, int rs, int imm);
int RtypeTest(int rd, int rs, int rt);
int JtypeTest(int address);
int ItypeTest(int rs, int rt, int imm);
int branchTest(int rs, int rt, int imm);
//register test
void registerTest();