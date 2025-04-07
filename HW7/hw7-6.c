#include <stdio.h>
#include <string.h>
#include "hw7-6.h"

char* ProcessingCommand(char (*string1)[21], char (*string2)[21], char *tastcase, int command_cnt, int test_mode) {
   
    // 因為傳入的是tastcase的reference，會直接改到測資的值，所以copy一份來執行ProcessingCommand   	
    static char memory[11]; 
    strcpy(memory, tastcase);
    
    // 持續迭代找每個command是否可以執行
    while (1) {
	
	// count是用來算有幾個command不能執行    
        int count = 0;

	// 每次都從第一個command開始判斷
        for (int i = 0; i < command_cnt; i++) {
            
	    // 判斷command是否可執行：該command的string1是否存在	
	    if (strstr(memory, string1[i]) == NULL) {
                count++;
                continue;
            }

            // 把memory中的string1替換成string2
	        // 找到strin1的位置後，先提取string1前面的部分到temp，再加上string2，最後再加上後面的部分，更新temp到memory
            char temp[51];
            char *str1 = strstr(memory, string1[i]);
            strncpy(temp, memory, str1 - memory);
            temp[str1 - memory] = '\0';
            strcat(temp, string2[i]);
            strcat(temp, str1 + strlen(string1[i]));
            strcpy(memory, temp);

            if (test_mode == 1) {
                printf("%s\n", memory);
            }
            
	    // 找到可執行的command後要離開這個for迴圈，重新從第一個command開始
	    break;
        }

	// 當不能執行的command數=總共command數時結束
        if (count == command_cnt) {
            break;
        }
    }

    return memory;
}