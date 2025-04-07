#include <stdio.h>
#include <string.h>
#include "hw7-1.h"


// 不用int而是用string裝輸入，可以解決像是輸入是01這種情況，也不用特別針對輸入的字元做處理
int GameStart(){

    char input[100];
    printf("Welcome to the game A = B, please select the level\n");
    
    fgets(input, sizeof(input), stdin);
    
    // 處理\n換行
    input[strcspn(input, "\n")] = '\0';

    // 判斷是否為 1/2（用字串形式判斷）
    if (strcmp(input, "1") == 0)
        return 1;
    else if (strcmp(input, "2") == 0)
        return 2;
    else	
        return -1;
}