#include <stdio.h>
#include <stdlib.h>

int f(int x, int y, int z){
	int result = ((x + z) ^ (y - z)) - (x & z & (y & 2024) | abs(z - y));
	return result;
}

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

int main(){
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	
	/* 這招好用，用3個for迴圈迭代所有可能（要注意i不能=j，j不能=k）
	int test[] = {a, b, c}; 
	int maximim;
	maximim = f(a, b, c);
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (i == j) continue;
			for (int k = 0; k < 3; k++){
				if (j == k) continue;
				int result = f(test[i], test[j], test[k]);
				if (result > maximim)
					maximim = result;
			}
		} 
	}
	*/
	
	int maximum = f(a, b, c);
	int array[3] = {a, b, c};
	for (int i = 0; i < 3; i++){
		int x = array[0];
		int y = array[1];
		int z = array[2];
		int result = f(x, y, z);
		if (result > maximum)
			maximum = result;
		x = array[0];
        y = array[2];
        z = array[1];
        result = f(x, y, z);
        if (result > maximum)
            maximum = result;
		if (i < 2)
			swap(&array[0], &array[i+1]);
	}

	printf("%d\n", maximum);
	return 0;
}