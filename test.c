#include "instruction_execution.h"
#include "memory.h"
#include "register.h"
extern unsigned int REGISTER[32];
extern int PC;

//R-Type
void addTest(int rd, int rs, int rt) {
	add(rd, rs, rt);
	if (REGISTER[rd] == REGISTER[rs] + REGISTER[rt]) {
		printf("add: Test Success\n");
	}
	else printf("add: Test Failed\n");
}

void subTest(int rd, int rs, int rt) {
	sub(rd, rs, rt);
	if (REGISTER[rd] == REGISTER[rs] - REGISTER[rt]) {
		printf("sub: Test Success\n");
	}
	else printf("sub: Test Failed\n");
}

void andTest(int rd, int rs, int rt) {
	aNd(rd, rs, rt);
	if (REGISTER[rd] == (REGISTER[rs] & REGISTER[rt])) {
		printf("and: Test Success\n");
	}
	else printf("and: Test Failed\n");
}

void orTest(int rd, int rs, int rt) {
	oR(rd, rs, rt);
	if (REGISTER[rd] == (REGISTER[rs] | REGISTER[rt])) {
		printf("or: Test Success\n");
	}
	else printf("or: Test Failed\n");
}

void xorTest(int rd, int rs, int rt) {
	xOr(rd, rs, rt);
	if (REGISTER[rd] == (REGISTER[rs] ^ REGISTER[rt])) {
		printf("xor: Test Success\n");
	}
	else printf("xor: Test Failed\n");
}

void norTest(int rd, int rs, int rt) {
	nor(rd, rs, rt);
	if (REGISTER[rd] == ~(REGISTER[rs] | REGISTER[rt])) {
		printf("nor: Test Success\n");
	}
	else printf("nor: Test Failed\n");
}

void sltTest(int rd, int rs, int rt) {
	slt(rd, rs, rt);
	if (REGISTER[rs] < REGISTER[rt]) {
		if (REGISTER[rd] == 1) {
			printf("slt: Test Success\n");
		}
		else printf("slt: Test Failed\n");
	}
	else {
		if (REGISTER[rd] == 0) printf("slt: Test Success\n");
		else printf("slt: Test Failed\n");
	}
}
//J-Type
void jalTest(int address){
	int prePC = PC;
	jal(address);
	if ((REGISTER[31] == prePC) && (PC == ((prePC + 4) & 0xf0000000) | (address << 2)))
	{
		printf("jal: Test Success\n");
	}
	else printf("jal: Test Failed\n");
}

void jTest(int address){
	int prePC = PC;
	j(address);
	if (PC == ((prePC + 4) & 0xf0000000) | (address << 2)) {
		printf("j: Test Success\n");
	}
	else printf("j: Test Failed\n");
}

void jrTest(int rs) {
	jr(rs);
	if (PC == REGISTER[rs]) {
		printf("jr: Test Success\n");
	}
	else printf("jr: Test Failed\n");
}
//Branch
void bltzTest(int rs, int rt,int imm) {
	int prePC = PC;
	if (REGISTER[rs] < 0) {
		if (PC == prePC + (imm * 4)) printf("bltz: Test Success\n");
		else printf("bltz: Test Failed\n");
	}
	else {
		if (PC == prePC) printf("bltz: Test Success\n");
		else printf("bltz: Test Failed\n");
	}
}
void beqTest(int rs, int rt, int imm) {
	int prePC = PC;
	if (REGISTER[rs] == REGISTER[rt]) {
		if (PC = prePC + (imm * 4)) {
			printf("beq: Test Success\n");
		}
		else printf("beq: Test Failed\n");
	}
	else {
		if (PC == prePC) printf("beq: Test Success\n");
		else printf("beq: Test Failed\n");
	}

}
void bneTest(int rs, int rt, int imm) {
	int prePC = PC;
	if (REGISTER[rs] != REGISTER[rt]) {
		if (PC = prePC + (imm * 4)) {
			printf("bne: Test Success\n");
		}
		else printf("bne: Test Failed\n");
	}
	else {
		if (PC == prePC) printf("bne: Test Success\n");
		else printf("bne: Test Failed\n");
	}
}
//I-Type
void addiTest(int rd, int rs, int imm) {
	addi(rd, rs, imm);
	if (REGISTER[rd] == REGISTER[rs] + imm) {
		printf("add: Test Success\n");
	}
	else printf("add: Test Failed\n");
}
void sltiTest(int rt, int rs, int imm) {

	slti(rt, rs, imm);
	if (REGISTER[rs] < imm) {
		if (REGISTER[rt] == 1) printf("slti: Test Success\n");
		else printf("slti:Test Failed\n");
	}
	else{
		if (REGISTER[rt] == 0) printf("slti: Test Success\n");
		else printf("slti:Test Failed\n");
	}
}
void andiTest(int rt, int rs, int imm) {
	addi(rt, rs, imm);
	if (REGISTER[rt] = REGISTER[rs] + imm) {
		printf("addi: Test Success\n");
	}
	else printf("addi: Test Failed\n");
}
void oriTest(int rt, int rs, int imm) {
	ori(rt, rs, rt);
	if (REGISTER[rt] = (REGISTER[rs] | imm)) {
		printf("ori: Test Success\n");
	}
	else printf("ori: Test Failed\n");
}
void xoriTest(int rt, int rs, int imm) {
	xori(rt, rs, rt);
	if (REGISTER[rt] = (REGISTER[rs] ^ imm)) {
		printf("xori: Test Success\n");
	}
	else printf("xori: Test Failed\n");
}


int RtypeTest(int rd, int rs, int rt) {
	addTest(rd, rs, rt);
	subTest(rd, rs, rt);
	andTest(rd, rs, rt);
	orTest(rd, rs, rt);
	xorTest(rd, rs, rt);
	norTest(rd, rs, rt);
	sltTest(rd, rs, rt);
	return 0;
}
int JtypeTest(int address) {
	jalTest(address);
	jTest(address);
	return 0;
}
int ItypeTest(int rs, int rt, int imm) {
	beqTest(rs, rt, imm);
	bneTest(rs, rt, imm);
	bltzTest(rs, 0, imm);
	sltiTest(rt, rs, imm);
	andiTest(rt, rs, imm);
	oriTest(rt, rs, imm);
	xoriTest(rt, rs, imm);
	return 0;
}
int branchTest(int rs, int rt, int imm) {
	beqTest(rs, rt, imm);
	bneTest(rs, rt, imm);
	bltzTest(rs, 0, imm);
	return 0;
}

void registerTest() {
	viewRegister();
	setRegister(1, 0x41);
	viewRegister();
	setRegister(31, 0x41);
	viewRegister();
	setRegister(1, 0x1f);
	viewRegister();
	setRegister(31, 0xff);
	viewRegister();
}