#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode.h"
#include "register.h"


extern char REGISTER_NAME[32][6];
void getInstructionStr(unsigned int inst, char** str) {

    union IR instruction = { inst };

    unsigned int opc = instruction.RI.opc;
    unsigned int fct = instruction.RI.fct;
    char* op = opc ? OPCODE_STR[opc] : FUNCT_STR[fct];
    char* rs = REGISTER_NAME[instruction.RI.rs];
    char* rt = REGISTER_NAME[instruction.RI.rt];
    char* rd = REGISTER_NAME[instruction.RI.rd];
    unsigned int sh = instruction.RI.sht;
    unsigned int address = instruction.JI.address;
    unsigned int immediate = instruction.II.operand;
    int signExtendedimm = (int)instruction.II.operand; // Sign Extendted

    if (opc == R_FORMAT) {
        switch (fct) {
        case SLL: case SRL: case SRA:
            sprintf(*str, "%s %s, %s, %d", op, rd, rt, sh);
            break;
        case JR:
            sprintf(*str, "%s %s", op, rs);
            break;
        case SYSCALL:
            sprintf(*str, "syscall");
            break;
        case MFHI: case MFLO:
            sprintf(*str, "%s %s", op, rd);
            break;
        default:
            sprintf(*str, "%s %s, %s, %s", op, rd, rs, rt);
        }
    }
    else {
        switch (opc) {
        case J: case JAL:
            sprintf(*str, "%s %x", op, address);
            break;
        case BLTZ:
            sprintf(*str, "%s %s, %d", op, rs, signExtendedimm);
            break;
        case BEQ: case BNE:
            sprintf(*str, "%s %s, %s, %d", op, rs, rt, signExtendedimm);
            break;
        case ADDI: case ADDIU: case SLTI: case SLTIU:
            sprintf(*str, "%s %s, %s, %d", op, rt, rs, signExtendedimm);
            break;
        case ANDI: case ORI: case XORI:
            sprintf(*str, "%s %s, %s, %d", op, rt, rs, immediate);
            break;
        case LUI:
            sprintf(*str, "%s %s, %d", op, rt, immediate);
            break;
        case LW: case SW: case LB: case SB: case LBU:
            sprintf(*str, "%s %s, %d(%s)", op, rt, signExtendedimm, rs);
            break;
        default:
            sprintf(*str, "[Unknown] Detect The Unknown Instuction -> %x", instruction.B);
        }
    }
}


void printInstructionStr(unsigned int inst) {
    char* str = (char*)malloc((100) * sizeof(char));
    getInstructionStr(inst, &str);
    printf("%s\n", str);
    free(str);
}