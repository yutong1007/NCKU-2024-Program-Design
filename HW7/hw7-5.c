#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hw7-5.h"

// 用bubble sort排序
void swap_array(char*ap1, char* ap2){
    char temp = *ap1; 
    *ap1 = *ap2; 
    *ap2 = temp; 
}

void Bubble_sort(char *array, int size){
    for (int round = 1; round < size; round++){
        for (int i = 0; i < (size - round); i++){
            if (array[i] > array[i+1]){ 
                swap_array(&array[i], &array[i+1]);
            }
        }
    }
}

// 知道輸入的大小就能用bubble sort排序
char* getAnswer2(char *tastcase){
    int len = strlen(tastcase); 
    Bubble_sort(tastcase, len);
    return tastcase;
}