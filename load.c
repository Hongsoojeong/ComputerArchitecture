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
void loadProgram(const char* filename) {

    FILE* fptr = NULL;

    if((fptr = fopen(filename, "rb")) == NULL) {
        printf("파일읽기 오류 \n");
        return;
    }

// 파일에서 읽은 바이너리를 저장할 버퍼
    unsigned char BINARY_BUFFER[1024];

// 바이너리 내용 BINARY_BUFFER에 저장하기
    for (int i = 0; i < 1024; i++) {
        int err = readChar(fptr, &BINARY_BUFFER[i]);
        if (err) break;
    }

    fclose(fptr); // 파일 읽기 끝

    // 명령어, 데이터 길이 구하기
    unsigned int num_instruction = invertEndian(((unsigned int*)BINARY_BUFFER)[0]);
    unsigned int num_data = invertEndian(((unsigned int*)BINARY_BUFFER)[1]);
    printf("\n");
   
    printf("========= Loading Program =========\n");
    printf("\n");
    printf("Insturction Count: %d\n", num_instruction);
    printf("    Data Count   : %d\n", num_data);
    printf("\n");
    // 프로그램, 스택 포인터 초기화
    PC = 0x400000;

    // 메모리, 레지스터 초기화
    resetMem();
    resetReg();
    printf("\n");
    printf("\n");
    printf("[Insturction] \n");
    // 명령어를 메모리에 적재하기
    for (int i = 0; i < num_instruction; i++) {
        int offset = i + 2; // 명령어 길이, 데이터 길이 워드 다음 인덱스
        unsigned int word = invertEndian(((unsigned int*)BINARY_BUFFER)[offset]);
        printInstruction(word);
        MEM(0x400000 + 4 * i, word, WRITE, WORD);
    }
    printf("\n");
    printf("\n");
    printf("[Data] \n");
    // 데이터를 메모리에 적재하기
        for (int i = 0; i < num_data; i++) {
            int offset = i + 2 + num_instruction; // 명령어 길이, 데이터 길이, 명령어 워드 다음 인덱스
            unsigned int word = invertEndian(((unsigned int*)BINARY_BUFFER)[offset]);
            printf("%x\n", word);
            MEM(0x10000000 + 4 * i, word, WRITE, WORD);
        }

        printf("===========   END   ===========");
        printf("\n");
        printf("\n");
}
