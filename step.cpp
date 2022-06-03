 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "memory.h"
 #include "register.h"
 #include "decode.h"
#include "alu.h"
#define _crt_secure_no_warnings
 //#include "instruction_execution.h"
 extern int HI;
 extern int LO;
 extern int PC;
#define ADD 8
#define SUB 9
#define SLL 1
#define SRL 2
#define SRA 3
#define SL 4
#define NOSHIFT 0
#define AND 12
#define OR 13
#define XOR 14
#define NOR 15
 void setPC(unsigned int val) {
	 PC = val;
	 return;
 }

 void jumpProgram(unsigned int address) {
   // PC를 address로 설정
   PC = address;
 }

 unsigned int getRiOp(IR ir) { return ir.RI.opcode; }
 unsigned int getRiRs(IR ir) { return ir.RI.rs; }
 unsigned int getRiRt(IR ir) { return ir.RI.rt; }
 unsigned int getRiRd(IR ir) { return ir.RI.rd; }
 unsigned int getRiSh(IR ir) { return ir.RI.shamt; }
 unsigned int getRiFn(IR ir) { return ir.RI.funct; }
 unsigned int getIiOp(IR ir) { return ir.II.op; }
 unsigned int getIiRs(IR ir) { return ir.II.rs; }
 unsigned int getIiRt(IR ir) { return ir.II.rt; }
 unsigned int getIiOper(IR ir) { return ir.II.op; }
 unsigned int getJiOp(IR ir) { return ir.JI.op; }
 unsigned int getJiAd(IR ir) { return ir.JI.address; }
 int stepProgram() {

   // 1. Instruction Fetch: 명령어 가져오기
     union IR instruction;
	 instruction.B = MEM(PC, 0, 0, 2);
	 char ins[10] = "\0";
     unsigned int riOp = getRiOp(instruction), riRs = getRiRs(instruction), riRt = getRiRt(instruction), riRd = getRiRd(instruction), riSh = getRiSh(instruction), riFn = getRiFn(instruction);
     unsigned int iiOp = getIiOp(instruction), iiRs = getIiRs(instruction), iiRt = getIiRt(instruction), iiOper = getIiOper(instruction);
     unsigned int jiOp = getJiOp(instruction), jiAd = getJiAd(instruction);
     unsigned int val = 0;
     int Z = 0;
	 switch (riOp) {
	 case 1:
		 strcpy_s(ins, "bltz"); //
		 printf("%s %d %d\n", ins, iiRs, iiOper * 4);
		 if (ALU(REG(iiRs, 0, 0), 0, SL, &Z) == 1)
			 setPC(PC + iiOper * 4 - 4);
		 break;
	 case 2:
		 strcpy_s(ins, "j");
		 printf("%s 0x%08x\n", ins, jiAd * 4);
		 setPC(jiAd * 4);
		 break;
	 case 3:
		 strcpy_s(ins, "jal");
		 printf("%s 0x%08x\n", ins, jiAd * 4);
		//ra =31
		 REG(31, PC, 1);
		 setPC(jiAd * 4);
		 break;
	 case 4: //
		 strcpy_s(ins, "beq");
		 printf("%s $%d, $%d, %d\n", ins, iiRs, iiRt, iiOper * 4);
		 if (ALU(REG(iiRs, 0, 0), REG(iiRt, 0, 0), SUB, &Z) == 0)
			 setPC(PC + iiOper * 4 - 4);
		 break;
	 case 5: //
		 strcpy_s(ins, "bne");
		 printf("%s $%d, $%d, %d\n", ins, iiRs, iiRt, iiOper * 4);
		 if (ALU(REG(iiRs, 0, 0), REG(iiRt, 0, 0), SUB, &Z) != 0)
			 setPC(PC + iiOper * 4 - 4);
		 break;

	 case 8:
		 strcpy_s(ins, "addi");

		 printf("%s $%d, $%d, %d\n", ins, iiRt, iiRs, (short)iiOper);
		 val = ALU(REG(iiRs, 0, 0), (short)iiOper, ADD, &Z);
		 //		printf("%d %d %d\n", iiOper, (short)iiOper, (int)iiOper);
		 REG(iiRt, val, 1); //!!
		 break;
	 case 10:
		 strcpy_s(ins, "slti");
		 printf("%s $%d, $%d, %d\n", ins, iiRt, iiRs, (short)iiOper);
		 val = ALU(REG(iiRs, 0, 0), iiOper, SL, &Z);
		 REG(iiRt, val, 1); //!!
		 break;
	 case 12:
		 strcpy_s(ins, "andi");
		 printf("%s $%d, $%d, %d\n", ins, iiRt, iiRs, (short)iiOper);
		 val = ALU(REG(iiRs, 0, 0), iiOper, AND, &Z);
		 //		printf("%d %d %d\n", iiOper, (short)iiOper, (int)iiOper);
		 REG(iiRt, val, 1); //!
		 break;
	 case 13:
		 strcpy_s(ins, "ori");
		 printf("%s $%d, $%d, %d\n", ins, iiRt, iiRs, (short)iiOper);
		 val = ALU(REG(iiRs, 0, 0), iiOper, OR, &Z);
		 //		printf("%d %d %d\n", iiOper, (short)iiOper, (int)iiOper);
		 REG(iiRt, val, 1);
		 break;
	 case 14:
		 strcpy_s(ins, "xori");
		 printf("%s $%d, $%d, %d\n", ins, iiRt, iiRs, (short)iiOper);
		 val = ALU(REG(iiRs, 0, 0), iiOper, XOR, &Z);
		 REG(iiRt, val, 1);
		 break;
	 case 15:
		 strcpy_s(ins, "lui"); //
		 printf("%s $%d, %d\n", ins, iiRt, (short)iiOper);
		 val = ALU(iiOper, 16, SLL, &Z);
		 REG(iiRt, val, 1);
		 break;

	 case 32:
		 strcpy_s(ins, "lb"); //바이트 단위로 데이터 로드
		 printf("%s $%d, %d($%d)\n", ins, iiRt, (short)iiOper, iiRs);
		 //Sign Extend to 32 bits in rt -> (int)
		 val = (int)MEM(REG(iiRs, 0, 0) + (short)iiOper, 0, 0, 2);
		 REG(iiRt, val, 1);
		 break;
	 case 35:
		 strcpy_s(ins, "lw"); //
		 printf("%s $%d, %d($%d)\n", ins, iiRt, (short)iiOper, iiRs);
		 val = MEM(REG(iiRs, 0, 0) + (short)iiOper, 0, 0, 2);
		 REG(iiRt, val, 1);
		 break;
	 case 36:
		 strcpy_s(ins, "lbu"); //
		 printf("%s $%d, %d($%d)\n", ins, iiRt, (short)iiOper, iiRs);
		 //Zero Extend to 32 bits in rt
		 val = (unsigned int)MEM(REG(iiRs, 0, 0) + (short)iiOper, 0, 0, 2);
		 REG(iiRt, val, 1);
		 break;

	 case 40:
		 strcpy_s(ins, "sb"); //
		 printf("%s $%d, %d($%d)\n", ins, iiRt, (short)iiOper, iiRs);
		 //Store just rightmost byte/halfword
		 MEM(REG(iiRs, 0, 0) + iiOper, (int)REG(iiRt, 0, 0), 1, 2);
		 break;
	 case 43:
		 strcpy_s(ins, "sw");
		 printf("%s $%d, %d($%d)\n", ins, iiRt, (short)iiOper, iiRs); //
		 MEM(REG(iiRs, 0, 0) + (short)iiOper, REG(iiRt, 0, 0), 1, 2);
		 break;
	 default:
		 switch (riFn) {
		 case 0:
			 strcpy_s(ins, "sll");
			 printf("%s $%d, $%d, %d\n", ins, riRd, riRt, riSh);
			 val = ALU(REG(riRt, 0, 0), riSh, SLL, &Z);
			 REG(riRd, val, 1);
			 break;
		 case 2:
			 strcpy_s(ins, "srl");
			 printf("%s $%d, $%d, %d\n", ins, riRd, riRt, riSh);
			 val = ALU(REG(riRt, 0, 0), riSh, SRL, &Z);
			 REG(riRd, val, 1);
			 break;
		 case 3:
			 strcpy_s(ins, "sra");
			 printf("%s $%d, $%d, %d\n", ins, riRd, riRt, riSh);
			 val = ALU(REG(riRt, 0, 0), riSh, SRA, &Z);
			 REG(riRd, val, 1);
			 break;

		 case 8:
			 strcpy_s(ins, "jr");
			 printf("%s $%d\n", ins, riRs);
			 //ra = 31
			 setPC(REG(31, 0, 0));
			 break;
		 case 12:
			 strcpy_s(ins, "syscall");
			 printf("%s %d\n", ins, REG(2, 0, 0));
			 if (REG(2, 0, 0) == 10)
				 setPC(0);
			 break;

		 case 16:
			 strcpy_s(ins, "mfhi"); //
			 printf("%s %d\n", ins, riRs);
			 REG(REG(riRs, 0, 0), HI, 1);
			 break;
		 case 18:
			 strcpy_s(ins, "mflo"); //
			 printf("%s %d", ins, riRs);
			 REG(REG(riRs, 0, 0), LO, 1);
			 break;

		 case 24:
			 strcpy_s(ins, "mul");
			 printf("%s $%d, $%d, $%d\n", ins, riRd, riRs, riRt);
			 REG(riRd, riRs * riRt, 1);
			 break;
		 case 32:
			 strcpy_s(ins, "add");
			 printf("%s $%d, $%d, $%d\n", ins, riRd, riRs, riRt);
			 val = (unsigned int)ALU(REG(riRs, 0, 0), REG(riRt, 0, 0), ADD, &Z);
			 REG(riRd, val, 1);
			 break;
		 case 34:
			 strcpy_s(ins, "sub");
			 printf("%s $%d, $%d, $%d\n", ins, riRd, riRs, riRt);
			 val = (unsigned int)ALU(REG(riRs, 0, 0), REG(riRt, 0, 0), SUB, &Z);
			 REG(riRd, val, 1);
			 break;
		 case 36:
			 strcpy_s(ins, "and");
			 printf("%s $%d, $%d, $%d\n", ins, riRd, riRs, riRt);
			 val = (unsigned int)ALU(REG(riRs, 0, 0), REG(riRt, 0, 0), AND, &Z);
			 REG(riRd, val, 1);
			 break;
		 case 37:
			 strcpy_s(ins, "or");
			 printf("%s $%d, $%d, $%d\n", ins, riRd, riRs, riRt);
			 val = (unsigned int)ALU(REG(riRs, 0, 0), REG(riRt, 0, 0), OR, &Z);
			 REG(riRd, val, 1);
			 break;
		 case 38:
			 strcpy_s(ins, "xor");
			 printf("%s $%d, $%d, $%d\n", ins, riRd, riRs, riRt);
			 val = (unsigned int)ALU(REG(riRs, 0, 0), REG(riRt, 0, 0), XOR, &Z);
			 REG(riRd, val, 1);
			 break;
		 case 39:
			 strcpy_s(ins, "nor");
			 printf("%s $%d, $%d, $%d\n", ins, riRd, riRs, riRt);
			 val = (unsigned int)ALU(REG(riRs, 0, 0), REG(riRt, 0, 0), NOR, &Z);
			 REG(riRd, val, 1);
			 break;
		 case 42:
			 strcpy_s(ins, "slt");
			 printf("%s $%d, $%d, $%d\n", ins, riRd, riRs, riRt);
			 val = (unsigned int)ALU(REG(riRs, 0, 0), REG(riRt, 0, 0), SL, &Z);
			 REG(riRd, val, 1);
			 break;
		 }
	 }
	 if (PC == 0)
		 return 404;
	 return 0;
 }
 void goProgram() {
	 // 프로그램 syscall 10까지 실행
	 while (1) {
		 int end = stepProgram();
		 if (end) return;
	 }
 }