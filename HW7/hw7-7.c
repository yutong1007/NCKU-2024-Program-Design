#include <stdio.h>
#include <string.h>
#include "hw7-7.h"

// 用遞迴的方式依序生成側資的每個位數的abc三種可能
// testcase要用指標的方式輸入進function，才可以在整個遞迴過程中共用這個testcase_index
void generate_each_test(int target_len, char (*all_testcase)[11], char *testcase, int digits_index, int *testcase_index){

    // 當位數=target_len時停止，將testcase複製到all_testcase
    if (digits_index == target_len){
        testcase[digits_index] = '\0';
        strcpy(all_testcase[*testcase_index], testcase);
        (*testcase_index)++;
        return;
    }

    // 遞迴依序對每個位數加上abc三種可能
    for (char c = 'a'; c <= 'c'; c++){
        testcase[digits_index] = c;
        
        // digits_index要在function裡面+1，不然會改到遞迴其他層的digits_index
        generate_each_test(target_len, all_testcase, testcase, digits_index + 1, testcase_index);
    }
}

void GeneratingTest(int target_len, char (*all_testcase)[11]){
    char testcase[11] = {0};
    int testcase_index = 0;
    generate_each_test(target_len, all_testcase, testcase, 0, &testcase_index);
}