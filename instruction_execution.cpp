
#include "memory.h"
#include "register.h"
#include "decode.h"
#include <stdio.h>
#include "ALU.h"



extern unsigned int REGISTER[32];
// register.c에 있는 PC와 HI, LO 값을 참조함
extern int PC;
extern int HI;
extern int LO;
int* z;
enum FROM_ALU {
    Add = 8,
    Sub = 9,
    And = 12,
    Or = 13,
    Xor = 14,
    Nor = 15,
    SetLess = 4
};


int add(int rd, int rs, int rt) {
    REGISTER[rd] = ALU(REGISTER[rs], REGISTER[rt], Add, NULL);
    printf("[ADD] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}


int addi(int rt, int rs, int imm) {
    REGISTER[rt] = ALU(REGISTER[rs], imm, Add, NULL);
    // printf("[ADDI] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

int sub(int rd, int rs, int rt) {
    REGISTER[rd] = ALU(REGISTER[rs], REGISTER[rt], Sub, NULL);
    printf("[SUB] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

int AND(int rd, int rs, int rt){
    REGISTER[rd] = ALU(REGISTER[rs], REGISTER[rt], And, NULL);
    //  printf("[AND] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}


int OR(int rd, int rs, int rt) {
    REGISTER[rd] = ALU(REGISTER[rs], REGISTER[rt], Or, NULL);
    //  printf("[OR] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

int XOR(int rd, int rs, int rt) {
    REGISTER[rd] = ALU(REGISTER[rs], REGISTER[rt], Xor, NULL);
    //   printf("[XOR] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

int nor(int rd, int rs, int rt) {
    REGISTER[rd] = ALU(REGISTER[rs], REGISTER[rt], Nor, NULL);
    //   printf("[NOR] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

//SET ON LESS THAN
int slt(int rd, int rs, int rt) {
    REGISTER[rd] = ALU(REGISTER[rs], REGISTER[rt], SetLess, NULL);
    //  printf("[SLT] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

//jump and link
//다음 명령어의 주소(PC+4)를 $ra에 저장하고 해당 address로 점프
int jal(int address) {
    int $ra = 31;
    REGISTER[$ra] = PC;
    PC = ((PC + 4) & 0xf0000000) | (address << 2);
    return 0;
}

// 0보다 작을 경우 분기 한다.
int bltz(int rs, int rt, int imm) {
    if (REGISTER[rs] < REGISTER[rt])
        PC += (imm * 4);
    return 0;
}

// beq는 두 피연산자를 비교해 같으면 새로운 주소로 이동, 같지 않으면 직후의 명령어를 수행
int beq(int rs, int rt, int imm) {
    if (REGISTER[rs] == REGISTER[rt])
        PC += (imm * 4);
    return 0;
}

// bne는 두 피연산자를 비교해 다르면 새로운 주소로 이동, 같으면 직후의 명령어를 수행
int bne(int rs, int rt, int imm) {
    if (REGISTER[rs] != REGISTER[rt])
        PC += (imm * 4);
    return 0;
}

int slti(int rt, int rs, int imm) {
    int ret;
    ret = REG(rs, 0, 0);
    if (ALU(ret, imm, 4, NULL)) REG(rt, rs, 1);
    return 0;
}

int andi(int rt, int rs, int imm) {
    int ret;
    ret = REG(rs, 0, 0);
    ALU(ret, imm, 0b1100, NULL);
    REG(rt, ret, 1);
    return 0;
}
int ori(int rt, int rs, int imm) {
    int ret;
    ret = REG(rs, 0, 0);
    ret = ALU(ret, imm, 0b1101, NULL);
    REG(rt, ret, 1);
    return 0;
}
int xori(int rt, int rs, int imm) {
    int ret;
    ret = REG(rs, 0, 0);
    ret = ALU(ret, imm, 0b1110, NULL);
    REG(rt, ret, 1);
    return 0;
}
int lui(int rt, int imm) {//load upper immediate
    REG(rt, (imm & 0xffff) << 16, 1);
    return 0;
}

int lw(int rt, int imm, int rs) {
    int ret;
    ret = MEM(REG(rs, 0, 0) + 4 * imm, 0, 0, 2);
    REG(rt, ret, 1);
    return 0;
}
int sw(int rt, int imm, int rs) {
    MEM(REG(rs, 0, 0) + 4 * imm, REG(rt, 0, 0), 1, 2);
    return 0;

}
int lb(int rt, int imm, int rs) {
    int ret;
    ret = MEM(REG(rs, 0, 0) + 4 * imm, 0, 0, 0);
    REG(rt, ret, 1);
    return 0;

}
int sb(int rt, int imm, int  rs) {
    MEM(REG(rs, 0, 0) + 4 * imm, REG(rt, 0, 0), 1, 0);
    return 0;

}
int lbu(int rt, int imm, int rs) {
    int ret;
    ret = MEM(REG(rs, 0, 0) + 4 * imm, 0, 0, 0);
    REG(rt, ret, 1);
    return 0;

}



int sll(int rd, int rt, int sh) {
    REGISTER[rd] = ALU(REGISTER[rt], sh, 1, NULL);
    printf("[SLL] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

int srl(int rd, int rt, int sh) {
    REGISTER[rd] = ALU(REGISTER[rt], sh, 2, NULL);
    printf("[SRL] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

int sra(int rd, int rt, int sh) {
    REGISTER[rd] = ALU(REGISTER[rt], sh, 3, NULL);
    printf("[SRA] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

int jr(int rs) {
    PC = REGISTER[rs];
    return 0;
}
int j(int address) {
    // PC ← {(PC + 4)[31:28], address, 00}
    PC = ((PC + 4) & 0xf0000000) | (address << 2);
    return 0;
}

int syscall()
{
    if (REGISTER[2] == 1)
    {
        printf("%d\n", REGISTER[4]);
        return 0;
    }
    if (REGISTER[2] == 10) {
        printf("exit program\n");
        return 1;
    }
    if (REGISTER[2] == 11) {
        printf("%c\n", REGISTER[4]);
        return 0;
    }

    return 0;
}

int mfhi(int rd) {
    REGISTER[rd] = HI;
    printf("[MFHI] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

int mflo(int rd) {

    REGISTER[rd] = LO;
    printf("[MFLO] : REGISTER[rd] %x\n", REGISTER[rd]);
    return 0;
}

int mul(int rs, int rt) {

    long long int result = (long long int)REGISTER[rs] * (long long int)REGISTER[rt];
    HI = result >> 32;
    LO = (result << 32) >> 32;
    printf("[MUL] : result %x\n", result);

    return 0;
}