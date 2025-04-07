#include <stdio.h>
/*
不用陣列做法
用array可以輕鬆紀錄每個人分到幾個糖果
*/

int main(){
    int N, C, K;
    scanf("%d %d %d", &N, &C, &K);

    // 記錄糖果數
    int candy = 0;
    
    // 紀錄這次分糖果是向右or向左（0是向右）
    int condition = 0;
    
    // 紀錄分到第幾位
    int counts = 1;
    
    // 持續分糖果
    while (C > 0){
        if (condition == 0){
                C--;
                counts++;
                if (counts == N){
                        C--;
                        condition = 1;
                        candy++;
                }
        }
        else {
                C--;
                counts--;
                if (counts == 1){
                        C--;
                        condition = 0;
                        candy++;
                }
        }
    }

    // 判斷輸出的candy要不要+1
    if (condition == 0){
        if (K < counts){
                printf("%d\n", candy + 1);
        }
        else {
                printf("%d\n", candy);
        }
    }
    else {
        if (K > counts){
                printf("%d\n", candy + 1);
        }
        else {
                printf("%d\n", candy);
        }
    }
    return 0;
}