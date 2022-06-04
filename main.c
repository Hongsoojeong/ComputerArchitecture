#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "register.h"
#include "load.h"
#include "step.h"

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
    int start = 0, end = 0;
    int EXIT = 1, is_loaded = 0, step_result = 0;

    while (EXIT) {
        printf("enter command: ");
        fflush(stdout);
        scanf("%s", cmd, 20 * sizeof(char));
        getchar();
        if (!strcmp(cmd, "x")) {
            printf("exit the program\n");
            EXIT = 0;
            break;
        }
        else if (!strcmp(cmd, "l")) { //load
            scanf("%s", filename, 20 * sizeof(char));
            getchar();
            loadProgram(filename);

        }
        else if (!strcmp(cmd, "m")) {
            scanf("%s", rn, 20 * sizeof(char));
            getchar();
            scanf("%s", value, 20 * sizeof(char));
            getchar();
            temp_rn = (unsigned int)strtoul(rn, NULL, 16);
            temp_v = (unsigned int)strtoul(value, NULL, 16);
            viewMemory(temp_rn, temp_v);
        }
        else if (!strcmp(cmd, "r")) {
            viewRegister();
        }
        else if (!strcmp(cmd, "g")) {
            goProgram();
            
        }
        else if (!strcmp(cmd, "s")) {
            stepProgram();
        }
        else if (!strcmp(cmd, "j")) {
            //jumpProgram();
        }
        else if (!strcmp(cmd, "sm")) {
            scanf("%s", rn);
            getchar();
            scanf("%s", value);
            getchar();
            temp_rn = atoi(rn);
            temp_v = (unsigned int)strtoul(value, NULL, 16);
            if (!temp_v)
                printf("Error value\n");
            else if ((temp_rn > 31) || (temp_rn < 0))
                printf("Error register number\n");
            setMemory(temp_rn, temp_v);
            /*else if (setMemory(temp_rn, temp_v))
                printf("Success set register\n");*/
            
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