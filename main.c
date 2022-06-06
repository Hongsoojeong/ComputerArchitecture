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
    char* val1 = (char*)malloc(sizeof(char) * 10); //input number
    char* val2 = (char*)malloc(sizeof(char) * 10); //input value
    unsigned int temp_v1, temp_v2;
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
            scanf("%s", val1, 20 * sizeof(char));
            getchar();
            printf("> Enter the End    : ");
            scanf("%s", val2, 20 * sizeof(char));
            getchar();
            temp_v1 = (unsigned int)strtoul(val1, NULL, 16);
            temp_v2 = (unsigned int)strtoul(val2, NULL, 16);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            viewMemory(temp_v1, temp_v2);
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
            scanf("%s", val1, 20 * sizeof(char));
            getchar();
            temp_v1 = (unsigned int)strtoul(val1, NULL, 16);
            jumpProgram(temp_v1);
        }
        else if (!strcmp(cmd, "sm")) {//set memory
            printf("> Enter the Memory :");
            scanf("%s", val1, 20 * sizeof(char));
            getchar();
            printf("> Enter the Value : ");
            scanf("%s", val2, 20 * sizeof(char));
            getchar();
            temp_v1 = (unsigned int)strtoul(val1, NULL, 16);
            temp_v2 = (unsigned int)strtoul(val2, NULL, 16);
            if (!temp_v2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("[Error] Value\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else if (setMemory(temp_v1, temp_v2)==-1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("[Error] Memory\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else printf("Success set memory\n");            
        }
        else if (!strcmp(cmd, "sr")) {//set register
            printf("> Enter the Register :");
            scanf("%s", val1);
            getchar();
            printf("> Enter the Value :");
            scanf("%s", val2);
            getchar();
            temp_v1 = atoi(val1);
            temp_v2 = (unsigned int)strtoul(val2, NULL, 16);

            if (!temp_v2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("[Error] Value\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            if ((temp_v1 > 31) || (temp_v1 < 0))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                printf("[Error] Register\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            else if (!setRegister(temp_v1, temp_v2))
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
    free(val1);
    free(val2);


    return 0;
}
