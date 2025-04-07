#include <stdio.h>
#include "pD.h"

// 資料用一個四維陣列裝，第一維是三維陣列的ID
// 用一個pointer分別指向兩個三為陣列，迭代交換
void exchange(int (*arr1)[20][20], int (*arr2)[20][20]){
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 20; j++){
			for (int k = 0; k < 20; k++){
				int temp = arr1[i][j][k];
				arr1[i][j][k] = arr2[i][j][k];
				arr2[i][j][k] = temp;
			}
		}
	}
}


void modify(int (*arr)[20][20], int *p, int x, int y, int z, int val){
	arr[x][y][z] = val;
	*p = x + y + z;
}

int get_value(int (*arr)[20][20][20], int id, int x, int y, int z){
	return arr[id][x][y][z];
}