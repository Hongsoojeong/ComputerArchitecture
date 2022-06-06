#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "register.h"
#include "load.h"
#include "step.h"
#include <Windows.h>
#include "test.h"
#define _crt_secure_no_warnings




int main(void) {
    char* cmd = (char*)malloc(sizeof(char) * 100); //command
    char* filename = (char*)malloc(sizeof(char) * 100);
    char* rn = (char*)malloc(sizeof(char) * 10); //input number
    char* value = (char*)malloc(sizeof(char) * 10); //input value
    unsigned int temp_rn, temp_v;
    int start = 0, end = 0;
    int EXIT = 1;


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

    system("title 컴퓨터 구조 프로젝트");
    printf("┌─────────────────────────────────────────────────┐\n");
    printf("│       ■■■    ■    ■     ■■   ■     ■      ■  ■■■  ■■■■■    ■■        ■      │\n");
    printf("│     ■               ■ ■  ■ ■   ■   ■       ■       ■       ■     ■     ■    ■ ■■■│\n");
    printf("│      ■■■    ■   ■    ■    ■   ■    ■    ■    ■ ■      ■    ■        ■  ■■       │\n");
    printf("│           ■   ■    ■    ■    ■   ■    ■  ■    ■    ■   ■    ■        ■  ■          │\n");
    printf("│          ■   ■    ■    ■    ■   ■    ■   ■    ■ ■■   ■     ■     ■     ■          │\n");
    printf("│  ■■■■    ■    ■    ■   ■    ■■■     ■           ■    ■    ■ ■    ■              │\n");
    printf("│                                                                                                  │\n");
    printf("│                                                                [컴퓨터 구조 프로젝트]            │\n");
    printf("└─────────────────────────────────────────────────┘\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                                     [ 가능한 명령어 ]   \n");
    printf("                                ① x :    Exit Program       \n");
    printf("                                ② l :    Load Program       \n");
    printf("                                ③ m :    View Memory        \n");
    printf("                                ④ sm :   Set Memory        \n");
    printf("                                ⑤ r :    View Register      \n");
    printf("                                ⑥ sr :   Set Register      \n");
    printf("                                ⑦ g :    Go with Program    \n");
    printf("                                ⑧ s :    Step with Program  \n");
    printf("                                ⑨ j :    jump with Program  \n");
    printf("                                ⑨ h :    help               \n");
    printf("\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    while (EXIT) {
        printf("\n");
        printf("[ Enter The Command ] : ");
        scanf("%s", cmd);
        getchar();
      
        if (!strcmp(cmd, "x")) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            printf("EXIT THE PROGRAM\n");
            EXIT = 0;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            break;
        }
        else if (!strcmp(cmd, "l")) { //load
            printf("> Enter the FileName  : ");
            scanf("%s", filename, 20 * sizeof(char));
            getchar();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
            loadProgram(filename);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        else if (!strcmp(cmd, "m")) { //view memory
            printf("> Enter the Start  : ");
            scanf("%s", rn, 20 * sizeof(char));
            getchar();
            printf("> Enter the End    : ");
            scanf("%s", value, 20 * sizeof(char));
            getchar();
            temp_rn = (unsigned int)strtoul(rn, NULL, 16);
            temp_v = (unsigned int)strtoul(value, NULL, 16);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            viewMemory(temp_rn, temp_v);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        else if (!strcmp(cmd, "r")) { //view register
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            viewRegister();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        else if (!strcmp(cmd, "g")) { //go
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            goProgram();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        else if (!strcmp(cmd, "s")) {//step
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            stepProgram();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        }
        else if (!strcmp(cmd, "j")) {//jump
            printf("> Enter The Address : ");
            scanf("%s", rn, 20 * sizeof(char));
            getchar();
            temp_rn = (unsigned int)strtoul(rn, NULL, 16);
            jumpProgram(temp_rn);
        }
        else if (!strcmp(cmd, "sm")) {//set memory
            printf("> Enter the Memory :");
            scanf("%s", rn, 20 * sizeof(char));
            getchar();
            printf("> Enter the Value : ");
            scanf("%s", value, 20 * sizeof(char));
            getchar();
            temp_rn = (unsigned int)strtoul(rn, NULL, 16);
            temp_v = (unsigned int)strtoul(value, NULL, 16);
            if (!temp_v)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("[Error] Value\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else if (setMemory(temp_rn, temp_v)==-1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("[Error] Memory\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else printf("Success set memory\n");            
        }
        else if (!strcmp(cmd, "sr")) {//set register
            printf("> Enter the Register :");
            scanf("%s", rn);
            getchar();
            printf("> Enter the Value :");
            scanf("%s", value);
            getchar();
            temp_rn = atoi(rn);
            temp_v = (unsigned int)strtoul(value, NULL, 16);

            if (!temp_v)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("[Error] Value\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            if ((temp_rn > 31) || (temp_rn < 0))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("[Error] Register\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else if (!setRegister(temp_rn, temp_v))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
                printf("Set Register Success!\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("Set Register Error\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
        }
        else if (!strcmp(cmd, "help")) {//help
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        printf("\n\n");
        printf("    [ Command] \n");
        printf("① x :    Exit Program       \n");
        printf("② l :    Load Program       \n");
        printf("③ m :    View Memory        \n");
        printf("④ sm :   Set Memory        \n");
        printf("⑤ r :    View Register      \n");
        printf("⑥ sr :   Set Register      \n");
        printf("⑦ g :    Go with Program    \n");
        printf("⑧ s :    Step with Program  \n");
        printf("⑨ j :    jump with Program  \n");
        printf("⑨ h :    help               \n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf("\n\n");
}
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            printf("Not Existed Command. Please Write the Correct Command\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
         
    }

    free(filename);
    free(cmd);
    free(rn);
    free(value);


    return 0;
}
