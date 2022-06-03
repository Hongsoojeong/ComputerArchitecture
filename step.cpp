// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "memory.h"
// #include "register.h"
// #include "decode.h"
// #include "instruction_execution.h"
// extern int HI;
// extern int LO;
// extern int PC;
// void goProgram() {
//   // 프로그램 syscall 10까지 실행
//   while (1) {
//     int end = stepProgram();
//     if (end) return;
//   }
// }
// void jumpProgram(unsigned int address) {
//   // PC를 address로 설정
//   PC = address;
// }
// union IR instructionFetch() {
//    // 1. PC 값을 읽어서 메모리에서 명령어 가져오기
//   unsigned int word = MEM(PC, 0, 0, 2);
//   union IR instruction = (union IR)word;
//   // 2. PC 값 4 상승
//   PC += 4;
//   return instruction;
// }
// int stepProgram() {

//   // 1. Instruction Fetch: 명령어 가져오기
//   union IR instruction = instructionFetch();

//   printf("실행한 명령어는 ");
//   // printInstruction(instruction.B);
//   //명령어 출력 (i)

//   // 임시로 명령어가 0x00000000이면 실행 중지
//   // 0x00000000인 명령어도 있지만 (sll 0 0 0)
//   // go 명령어 실행 시 멈출 방법이 없기 때문
//   if (instruction.B == 0) return 1;

//   // 2. Instruction Decode: 명령어 해석
//   unsigned int opcode = instruction.RI.opcode;
//   unsigned int funct = instruction.RI.funct;
//   unsigned int rs = instruction.RI.rs;
//   unsigned int rt = instruction.RI.rt;
//   unsigned int rd = instruction.RI.rd;
//   unsigned int sh = instruction.RI.shamt;
//   unsigned int address = instruction.JI.address;
//   unsigned int u_imm = instruction.II.immediate & 0xffff;
//   int imm = instruction.II.immediate; // Sign Extendted

//   // 3. EX, MA, RW: 명령어를 분기하고 해당되는 함수 실행
//   if (opcode == R_FORMAT) {
//     switch (funct) {
//       case SLL:     return sll(rd, rt, sh);
//       case SRL:     return srl(rd, rt, sh);
//       case SRA:     return sra(rd, rt, sh);
//       case JR:      return jr(rs);
//       case SYSCALL: return syscall();
//       case MFHI:    return mfhi(rd);
//       case MFLO:    return mflo(rd);
//       case MUL:     return mul(rs, rt);
//       case ADD:     return add(rd, rs, rt);
//       case SUB:     return sub(rd, rs, rt);
//       case AND:     return and(rd, rs, rt);
//       case OR:      return or(rd, rs, rt);
//       case XOR:     return xor(rd, rs, rt);
//       case NOR:     return nor(rd, rs, rt);
//       case SLT:     return slt(rd, rs, rt);
//       default:      printf("잘못된 명령어입니다\n");
//     }
//   } else {
//     switch (opcode) {
//       case J:    return j(address);
//       case JAL:  return jal(address);
//       case BLTZ: return bltz(rs, rt, imm);
//       case BEQ:  return beq(rs, rt, imm); 
//       case BNE:  return bne(rs, rt, imm);
//       case ADDI: return addi(rt, rs, imm);
//       case SLTI: return slti(rt, rs, imm);
//       case ANDI: return andi(rt, rs, u_imm);
//       case ORI:  return ori(rt, rs, u_imm);
//       case XORI: return xori(rt, rs, u_imm);
//       case LUI:  return lui(rt, u_imm);
//       case LW:   return lw(rt, imm, rs);
//       case SW:   return sw(rt, imm, rs);
//       case LB:   return lb(rt, imm, rs);
//       case SB:   return sb(rt, imm, rs);
//       case LBU:  return lbu(rt, imm, rs);
//       default:   printf("잘못된 명령어입니다\n");
//     }
//   }

//   return 1; // 프로그램 끝났으면 1 반환, 아니면 0 반환
// }