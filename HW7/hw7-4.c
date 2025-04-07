#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hw7-4.h"

char edit_tastcase[51];
char* getAnswer1(char *tastcase){
    
    // tastcase 的 index
    int counter1 = 0;
    
    // 處理後的 char array 
    int counter2 = 0;
    
    while (counter1 < 51){
        // 先看是不是a
        if (tastcase[counter1] == 'a'){
            // 看是不是連續a 什麼都不做
            if (tastcase[counter1+1] == 'a' || tastcase[counter1-1] == 'a'){
                counter1++;
            }
            // 不是a的話 加進array
            else {
                edit_tastcase[counter2] = tastcase[counter1];
                counter1++;
                counter2++;
            }
        }

        // 不是a 直接加進array
        else {
            edit_tastcase[counter2] = tastcase[counter1];
            counter1++;
            counter2++;
        }
    }
    return edit_tastcase;
}