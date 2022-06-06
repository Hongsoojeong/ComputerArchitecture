#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "register.h"
#include "decode.h"
#include "step.h"
#include "main.h"


enum READ_WRITE { READ, WRITE };
enum SIZE { BYTE, HALF_WORD, WORD };

extern int PC;
int readChar(FILE* fp, unsigned char* c) {
    if (fread(c, 1, 1, fp) != 1) return 1;
    else return 0;
}
unsigned int invertEndian(unsigned int data)
{
    unsigned char c[4];

    c[3] = (unsigned char)data; data = data >> 8;
    c[2] = (unsigned char)data; data = data >> 8;
    c[1] = (unsigned char)data; data = data >> 8;
    c[0] = (unsigned char)data;

    return *(unsigned int*)c;
}
void loadProgram(const char* filename) {
    // read file
    FILE* fptr = NULL;

    if((fptr = fopen(filename, "rb")) == NULL) {
        printf("ÆÄÀÏÀÐ±â ¿À·ù \n");
        return;
    }

    unsigned char BINARY_BUFFER[1024];


    for (int i = 0; i < 1024; i++) {
        int err = readChar(fptr, &BINARY_BUFFER[i]);
        if (err) break;
    }

    fclose(fptr); 
   

    
    unsigned int instructionLen = invertEndian(((unsigned int*)BINARY_BUFFER)[0]); // length of instruction
    unsigned int dataLen = invertEndian(((unsigned int*)BINARY_BUFFER)[1]); //length of data
    printf("\n");
   
    printf("========= Loading Program =========\n");
    printf("\n");
    printf("Insturction Count: %d\n", instructionLen);
    printf("    Data Count   : %d\n", dataLen);
    printf("\n");

    // initialize PC, SP, register, memory
    PC = 0x400000;
    resetMem();
    resetReg();
    printf("\n");
    printf("\n");

   
    // load instructions from buffer to memory
    printf("[Insturction] \n");
    for (int i = 0; i < instructionLen; i++) {
        int offset = i + 2; 
        unsigned int word = invertEndian(((unsigned int*)BINARY_BUFFER)[offset]);
        printInstruction(word);
        MEM(0x400000 + 4 * i, word, WRITE, WORD);
    }
    printf("\n");
    printf("\n");

    // load data from buffer to memory
    printf("[Data] \n");
    for (int i = 0; i < dataLen; i++) {
        int offset = i + 2 + instructionLen; 
        unsigned int word = invertEndian(((unsigned int*)BINARY_BUFFER)[offset]);
        printf("%x\n", word);
        MEM(0x10000000 + 4 * i, word, WRITE, WORD);
    }

    printf("===========   END   ===========");
    printf("\n");
    printf("\n");
}
