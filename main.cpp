#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "register.h"

#define _crt_secure_no_warnings

#define buffer_size 1024
#define memory_size 0x100000
#define register_size 32

unsigned int invertEndian(unsigned int data)
{
    unsigned char c[4];

    c[3] = (unsigned char)data; data = data >> 8;
    c[2] = (unsigned char)data; data = data >> 8;
    c[1] = (unsigned char)data; data = data >> 8;
    c[0] = (unsigned char)data;

    return *(unsigned int*)c;
}

int main(void) {
    char* cmd = (char*)malloc(sizeof(char) * 100); //command
    char* filename = (char*)malloc(sizeof(char) * 100);
    char* rn = (char*)malloc(sizeof(char) * 10); //input number
    char* value = (char*)malloc(sizeof(char) * 10); //input value
    unsigned int temp_rn, temp_v;
    int EXIT = 1, is_loaded = 0, step_result = 0;

    while (EXIT) {
        printf("enter command: ");
        fflush(stdout);
        scanf_s("%s", cmd, 20 * sizeof(char));
        getchar();
        if (!strcmp(cmd, "x")) {
            printf("exit the program\n");
            EXIT = 0;
            break;
        }
        else if (!strcmp(cmd, "l")) { //load
            errno_t err;
            FILE* fptr = NULL;
            err = fopen_s(&fptr, "as_ex01_arith.bin", "rb");
            if (err) {
                printf("can not open file\n");
                break;
            }
            else {
                printf("file is opened\n");
            }

            unsigned char binary_buffer[1024];
            unsigned int data;
            unsigned int addr;

            unsigned int iCount;   // # of instructions
            unsigned int dCount;   // # of data
            // read instruction and data numbers

            if (fread(&data, sizeof(data), 1, fptr) < 0) {
                printf("!");
            }


            iCount = invertEndian(data);
            fread(&data, sizeof(data), 1, fptr);
            dCount = invertEndian(data);
            printf("number of instructions: %d, number of data: %d\n", iCount, dCount);

            //=======================================================
            // load to memory
            //resetMem();
            //resetReg();

        // Load to memory
            addr = 0;
            for (int i = 0; i < (int)iCount; i++) {
                fread(&data, sizeof(unsigned int), 1, fptr);
                data = invertEndian(data);
                MEM(0x400000 + 4 * i, data, 1, 2);
                addr += 4;
            }
            for (int i = 0; i < (int)dCount; i++) {
                fread(&data, sizeof(unsigned int), 1, fptr);
                data = invertEndian(data);
                //printf("파일에서 읽은 데이터: %x\n", data);
                MEM(0x10000000 + 4 * i, data, 1, 2);

            }

            fclose(fptr);

        }
        else if (!strcmp(cmd, "m")) {
            unsigned int start = 0, end = 1048576;
            viewMemory(start, end);
        }
        else if (!strcmp(cmd, "r")) {
            viewRegister();
        }
        else if (!strcmp(cmd, "g")) {
            //goProgram();
            
        }
        else if (!strcmp(cmd, "s")) {
            //stepProgram();
        }
        else if (!strcmp(cmd, "j")) {
            //jumpProgram();
        }
        else if (!strcmp(cmd, "sm")) {
            scanf_s("%s", rn);
            getchar();
            scanf_s("%s", value);
            getchar();
            temp_rn = atoi(rn);
            temp_v = (unsigned int)strtoul(value, NULL, 16);
            if (!temp_v)
                printf("Error value\n");
            if ((temp_rn > 31) || (temp_rn < 0))
                printf("Error register number\n");
            else {
                printf("Success set register\n");
            }
        }
        else if (!strcmp(cmd, "sr")) {
            scanf_s("%s", rn);
            getchar();
            scanf_s("%s", value);
            getchar();
            temp_rn = atoi(rn);
            temp_v = (unsigned int)strtoul(value, NULL, 16);
            if (!temp_v)
                printf("Error value\n");
            if ((temp_rn > 31) || (temp_rn < 0))
                printf("Error register number\n");
            else if (setRegister(temp_rn, temp_v))
                printf("Success set register\n");
            else
                printf("Error set register\n");
        }

         
    }
    printf("program exit\n");
    free(filename);
    free(cmd);
    free(rn);
    free(value);


    return 0;
}