#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

const int M_SIZE = 0x100000;
unsigned char progMEM[0x100000], dataMEM[0x100000], stakMEM[0x100000]; //MiB


int MEM(unsigned int A, int V, int nRW, int S) {
	unsigned int sel, offset;
	unsigned char* pM;
	sel = A >> 20; offset = A & 0xFFFFF;
	//address decoding and select a physical memory


	if (sel == 0x004) pM = progMEM; //program memory
	else if (sel == 0x100) pM = dataMEM; //data memory
	else if (sel == 0x7FF)pM = stakMEM; //stack
	else {
		printf("\n");
		printf("<<<<< [Error] Wrong Memory Access >>>>>\n");
		printf("\n");
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
			printf("[Error] Unaligned Access\n");
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
			printf("[Error] Unaligned Access\n");
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

void resetMem()
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
	printf("\n\n");
	printf("========= View Memory =========");
	printf("\n\n");
	for (unsigned int add = start; add <= end; add += 4) {
		int val = MEM(add, 0, 0, 2);
		printf("%x : %x \n", add, val);
	}
	printf("\n");
	printf("=========== END ===========");
	printf("\n\n");
}
int setMemory(unsigned int A, int V)
{
	return MEM(A, V, 1, 2);
}


