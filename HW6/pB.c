#include <stdio.h>
#include "pB.h"

int C[100][100];

void solve(int n, int m, int (*A)[100], int (*B)[100]){
	// 迭代array中每個元素相加，存在一個新定義的C array
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			C[i][j] = A[i][j] + B[i][j];
		}
	}	
}

int get_value(int x, int y){	
	return C[x][y];
}