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
    unsigned int word = MEM(PC, 0, 0, 2);
    union IR instruction = { word };
    PC += 4;
    return instruction;
}

int stepProgram() {

    union IR instruction = instructionFetch();
    printf("\n");
    printf("> Excuting Instruction < \n");
    printInstruction(instruction.B);

    if (instruction.B == 0) return 1;

    //   // 2. Instruction Decode: ���ɾ� �ؼ�
    unsigned int opcode = instruction.RI.opcode;
    unsigned int funct = instruction.RI.funct;
    unsigned int rs = instruction.RI.rs;
    unsigned int rt = instruction.RI.rt;
    unsigned int rd = instruction.RI.rd;
    unsigned int sh = instruction.RI.shamt;
    unsigned int address = instruction.JI.address;
    unsigned int u_imm = instruction.II.operand & 0xffff;
    int imm = instruction.II.operand; // Sign Extendted

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
            case ADD:     return add(rd, rs, rt);
            case SUB:     return sub(rd, rs, rt);
            case AND:     return aNd(rd, rs, rt);
            case OR:      return oR(rd, rs, rt);
            case XOR:     return xOr(rd, rs, rt);
            case NOR:     return nor(rd, rs, rt);
            case SLT:     return slt(rd, rs, rt);
            default:      printf("[Unknown] Instuction\n");
        }
    }
    else {
        switch (opcode) {
            case J:    return j(address);
            case JAL:  return jal(address);
            case BLTZ: return bltz(rs, 0, imm);
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
            default:   printf("[Unknown] Instuction\n");
        }
    }
    printf("\n");
    printf("============== END ==============\n\n");
    return 1; 
}
void goProgram()
{
    while (1) {
        int end = stepProgram();
        if (end) return;
    }
}
void jumpProgram(unsigned int address) {
    PC = address;
}