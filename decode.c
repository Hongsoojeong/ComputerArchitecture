#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode.h"
#include "register.h"


extern char REGISTER_NAME[32][6];
void instructionToString(unsigned int word, char** str) {

    union IR instruction = { word };

    unsigned int opcode = instruction.RI.opcode;
    unsigned int funct = instruction.RI.funct;
    char* op = opcode ? OPCODE_STR[opcode] : FUNCT_STR[funct];
    char* rs = REGISTER_NAME[instruction.RI.rs];
    char* rt = REGISTER_NAME[instruction.RI.rt];
    char* rd = REGISTER_NAME[instruction.RI.rd];
    unsigned int sh = instruction.RI.shamt;
    unsigned int target = instruction.JI.address;
    unsigned int u_immediate = instruction.II.immediate;
    int immediate = (int)instruction.II.immediate; // Sign Extendted

    if (opcode == R_FORMAT) {
        switch (funct) {
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
        switch (opcode) {
        case J: case JAL:
            sprintf(*str, "%s %x", op, target);
            break;
        case BLTZ:
            sprintf(*str, "%s %s, %d", op, rs, immediate);
            break;
        case BEQ: case BNE:
            sprintf(*str, "%s %s, %s, %d", op, rs, rt, immediate);
            break;
        case ADDI: case ADDIU: case SLTI: case SLTIU:
            sprintf(*str, "%s %s, %s, %d", op, rt, rs, immediate);
            break;
        case ANDI: case ORI: case XORI:
            sprintf(*str, "%s %s, %s, %d", op, rt, rs, u_immediate);
            break;
        case LUI:
            sprintf(*str, "%s %s, %d", op, rt, u_immediate);
            break;
        case LW: case SW: case LB: case SB: case LBU:
            sprintf(*str, "%s %s, %d(%s)", op, rt, immediate, rs);
            break;
        default:
            sprintf(*str, "Unknown Instruction: %x", instruction.B);
        }
    }
}

// 명령어 출력하기
void printInstruction(unsigned int word) {
    char* str = (char*)malloc((100) * sizeof(char));
    instructionToString(word, &str);
    printf("%s\n", str);
    free(str);
}