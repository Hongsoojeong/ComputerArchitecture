#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

//#include "register.h"
//#include "decode.h"
//#include "step.c"
//#include "instruction_execution.h"
#define PROG_START 0x00400000
#define PROG_END 0x00500000
#define DATA_START 0x10000000
#define DATA_END 0x10100000
#define STAK_START 0x7FF00000
#define STAK_END 0x80000000

const int M_SIZE = 0x100000;
unsigned char progMEM[0x100000], dataMEM[0x100000], stakMEM[0x100000]; //MiB

// enum accessType { RD, WR };
// enum accessSize { BYTE, HALF, WORD };

int MEM(unsigned int A, int V, int nRW, int S) {
	unsigned int sel, offset;
	unsigned char* pM;
	sel = A >> 20; offset = A & 0xFFFFF;
	//address decoding and select a physical memory


	if (sel == 0x004) pM = progMEM; //program memory
	else if (sel == 0x100) pM = dataMEM; //data memory
	else if (sel == 0x7FF)pM = stakMEM; //stack
	else {
		printf("Error: �߸��� �޸� �ּ�\n");
		return -1;
	}
	//offset processing for alignment
	if (S == 0) {//byte
		if (nRW == 0) { //read
			return pM[offset];
		}
		else if (nRW == 1) {//write
			pM[offset] = (unsigned char)V;
			return 1;
		}
	}
	else if (S == 1) {//half word
		printf("%x", offset);
		if ((offset & 1) != 0) {
			printf("Unaligned access error");
			offset &= 0xfffffffe;
		}
		if (nRW == 0) { //read
			return (pM[offset] << 8) + pM[offset + 1];
		}
		else if (nRW == 1) {//write
			pM[offset] = (unsigned char)((V >> 8) & 0xff);
			pM[offset + 1] = (unsigned char)(V & 0xff);
			return 1;
		}
	}
	else if (S == 2) {//word
		if ((offset & 3) != 0) {
			printf("Unaligned access error");
			offset &= 0xfffffffc;
		}
		if (nRW == 0) { //read
			return (pM[offset] << 24) + (pM[offset + 1] << 16) + (pM[offset + 2] << 8) + pM[offset + 3];
		}
		else if (nRW == 1) {//write
			pM[offset] = (unsigned char)((V >> 24) & 0xff);
			pM[offset + 1] = (unsigned char)((V >> 16) & 0xff);
			pM[offset + 2] = (unsigned char)((V >> 8) & 0xff);
			pM[offset + 3] = (unsigned char)(V & 0xff);
			return 1;
		}
	}
	else {//error
		exit(1);
	}
	return 0;
}

void resetMem(void)
{
	int i;
	for (i = 0; i < M_SIZE; i++) {
		progMEM[i] = 0;
		dataMEM[i] = 0;
		stakMEM[i] = 0;
	}
}

void viewMemory(unsigned int start, unsigned int end)
{
	for (unsigned int add = start; add <= end; add += 4) {
		int val = MEM(add, 0, 0, 2);
		printf("%x : %x \n", add, val);
	}
}
void setMemory(unsigned int A, int V)
{
	MEM(A, V, 1, 2);
}


