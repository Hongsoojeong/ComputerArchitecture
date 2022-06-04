#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "register.h"
#include "decode.h"
#include "instruction_execution.h"

extern int HI;
extern int LO;
extern int PC;

union IR instructionFetch() {
    // 1. PC ���� �о �޸𸮿��� ���ɾ� ��������
    unsigned int word = MEM(PC, 0, 0, 2);
    //union IR instruction = (union IR)word;
    union IR instruction = { word };
    // 2. PC �� 4 ���
    PC += 4;
    return instruction;
}

int stepProgram() {

    // 1. Instruction Fetch: ���ɾ� ��������
    union IR instruction = instructionFetch();
    //printf("instruction.B : %d\n", instruction);Ȯ�ο�
    printf("Executed instruction:\n");
    printInstruction(instruction.B);
 //���ɾ� ��� (i)

//   // �ӽ÷� ���ɾ 0x00000000�̸� ���� ����
//   // 0x00000000�� ���ɾ ������ (sll 0 0 0)
//   // go ���ɾ� ���� �� ���� ����� ���� ����
    if (instruction.B == 0) return 1;

    //   // 2. Instruction Decode: ���ɾ� �ؼ�
    unsigned int opcode = instruction.RI.opcode;
    unsigned int funct = instruction.RI.funct;
    unsigned int rs = instruction.RI.rs;
    unsigned int rt = instruction.RI.rt;
    unsigned int rd = instruction.RI.rd;
    unsigned int sh = instruction.RI.shamt;
    unsigned int address = instruction.JI.address;
    unsigned int u_imm = instruction.II.immediate & 0xffff;
    int imm = instruction.II.immediate; // Sign Extendted
    //printf("opcode: %x, funct: %x, rs:%x, rt:%x, rd:%x, sh:%x, address:%x, u_imm:%x, imm:%x\n", opcode, funct, rs, rt, rd, sh, address, u_imm, imm);

   // 3. EX, MA, RW: ���ɾ �б��ϰ� �ش�Ǵ� �Լ� ����
    if (opcode == R_FORMAT) {
        switch (funct) {
            case SLL:     return sll(rd, rt, sh);
            case SRL:     return srl(rd, rt, sh);
            case SRA:     return sra(rd, rt, sh);
            case JR:      return jr(rs);
            case SYSCALL: return syscall();
            case MFHI:    return mfhi(rd);
            case MFLO:    return mflo(rd);
            case MUL:     return mul(rs, rt);
            case ADD:     return addTest(rd, rs, rt);
            case SUB:     return sub(rd, rs, rt);
            case AND:     return aNd(rd, rs, rt);
            case OR:      return oR(rd, rs, rt);
            case XOR:     return xOr(rd, rs, rt);
            case NOR:     return nor(rd, rs, rt);
            case SLT:     return slt(rd, rs, rt);
            default:      printf("�߸��� ���ɾ��Դϴ�\n");
        }
    }
    else {
        switch (opcode) {
            case J:    return j(address);
            case JAL:  return jal(address);
            case BLTZ: return bltz(rs, rt, imm);
            case BEQ:  return beq(rs, rt, imm);
            case BNE:  return bne(rs, rt, imm);
            case ADDI: return addi(rt, rs, imm);
            case SLTI: return slti(rt, rs, imm);
            case ANDI: return andi(rt, rs, u_imm);
            case ORI:  return ori(rt, rs, u_imm);
            case XORI: return xori(rt, rs, u_imm);
            case LUI:  return lui(rt, u_imm);
            case LW:   return lw(rt, imm, rs);
            case SW:   return sw(rt, imm, rs);
            case LB:   return lb(rt, imm, rs);
            case SB:   return sb(rt, imm, rs);
            case LBU:  return lbu(rt, imm, rs);
            default:   printf("�߸��� ���ɾ��Դϴ�\n");
        }
    }

    return 1; // ���α׷� �������� 1 ��ȯ, �ƴϸ� 0 ��ȯ
}
void goProgram()
{
    // ���α׷� syscall 10���� ����
    while (1) {
        int end = stepProgram();
        if (end) return;
    }
}
void jumpProgram(unsigned int address) {
    // PC�� address�� ����
    PC = address;
}