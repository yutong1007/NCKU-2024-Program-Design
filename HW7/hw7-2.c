#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw7-2.h"


char* getUserInput(){
    // 用動態記憶體分配使記憶體分配到heap memory，不是stack memory，function結束後不會被清除
    char* command = (char*)malloc(21 * sizeof(char));
    fgets(command, 21, stdin);
    command[strcspn(command, "\n")] = '\0';
    return command;
}

void printAllInput(char (*command)[21], int command_cnt){
    // command_cnt = 指令總數
    for (int i = 0; i < command_cnt; i++)
        printf("%s\n", command[i]);
}