#include <stdio.h>
#include "pC.h"

void f(int n, int *p){
	
	// 用遞迴做，call by reference不能做recursion
	int result = 0;
	
	// n >= 1，第一個數和第二個數都是1
	if (n <= 2)
		result = 1;
	else {
		int f1 = 0;
		int f2 = 1;
		for (int i = 3; i <= n+1; i++){
			result = f1 + f2;
			f1 = f2;
			f2 = result;
		}
	}
	
	// 用指標直接更改該位置的值
	*p = result;
}