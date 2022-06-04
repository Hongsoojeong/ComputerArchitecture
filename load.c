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
        printf("�����б� ���� \n");
        return;
    }

// ���Ͽ��� ���� ���̳ʸ��� ������ ����
    unsigned char BINARY_BUFFER[1024];

// ���̳ʸ� ���� BINARY_BUFFER�� �����ϱ�
    for (int i = 0; i < 1024; i++) {
        int err = readChar(fptr, &BINARY_BUFFER[i]);
        if (err) break;
    }

    fclose(fptr); // ���� �б� ��

    // ��ɾ�, ������ ���� ���ϱ�
    unsigned int num_instruction = invertEndian(((unsigned int*)BINARY_BUFFER)[0]);
    unsigned int num_data = invertEndian(((unsigned int*)BINARY_BUFFER)[1]);

    printf("��ɾ� ����: %d\n", num_instruction);
    printf("������ ����: %d\n", num_data);

    // ���α׷�, ���� ������ �ʱ�ȭ
    PC = 0x400000;

    // �޸�, �������� �ʱ�ȭ
    resetMem();
    resetReg();

    // ��ɾ �޸𸮿� �����ϱ�
    for (int i = 0; i < num_instruction; i++) {
        int offset = i + 2; // ��ɾ� ����, ������ ���� ���� ���� �ε���
        unsigned int word = invertEndian(((unsigned int*)BINARY_BUFFER)[offset]);
        printf("���� ��ɾ�: "); 
        printInstruction(word);
        MEM(0x400000 + 4 * i, word, WRITE, WORD);
    }

    // �����͸� �޸𸮿� �����ϱ�
        for (int i = 0; i < num_data; i++) {
            int offset = i + 2 + num_instruction; // ��ɾ� ����, ������ ����, ��ɾ� ���� ���� �ε���
            unsigned int word = invertEndian(((unsigned int*)BINARY_BUFFER)[offset]);
            printf("���� ������: %x\n", word);
            MEM(0x10000000 + 4 * i, word, WRITE, WORD);
        }
}
