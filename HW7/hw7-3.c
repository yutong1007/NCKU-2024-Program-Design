#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hw7-3.h"


void ParsingData(char command[21], char string1[21], char string2[21]){
    
    // 因為string1也有可能出現=，所以用=空格來當作string1 string2的切割點
    // 用一個指標指向切割點，判斷string1長度	
    char *equal = strstr(command, " =");
    size_t string1_length = equal - command;
    
    // 將command前string1長度（也就是string1）提取出來
    strncpy(string1, command, string1_length);
    string1[string1_length] = '\0';

    // string2可能是空的
    if (*(equal + 1) == '\0') {
        string2[0] = '\0';
        return;
    }

    // equal+3是跳過空格=空格
    strncpy(string2, equal + 3, 20);
    string2[20] = '\0';
}