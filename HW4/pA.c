#include <stdio.h>
#define size 32

int main(){
	int N;
	scanf("%d", &N);
	
	if (N == 1){
		int X;
		scanf("%d", &X);
				
		for (int i = 31; i >= 0; i--){
			int bit;
			// 每次向右shift依序從左到右取出一個bit，和1做&，如果都是1則輸出1，(0,1)則輸出0
			bit = (X >> i) & 1;
			printf("%d", bit);
		}
		printf("\n");
	}

	if (N == 2){
		float X;
		scanf("%f", &X);
		
		// float不能用bitwise operator，所以用一個int pointer指向float的32 bit binary，用int pointer做位元操作
		int *x;
	    x = (int*) &X;
		for (int i = 31; i >= 0; i--){
			int bit;
			// *x是該位置的值（也就是他的32 bit binary）
			bit = (*x >> i) & 1;
			printf("%d", bit);
		}
		printf("\n");
	}	
	/*
	手刻
	// 判斷int or float
	int N;
	scanf("%d", &N);
	
	// 裝32bit
	int bit[size] = {};

	// int
	if (N == 1){
		int X;
		scanf("%d", &X);
		
		// 正數
		if (X > 0){
			for (int i = 31; i >= 0; i--){
				bit[i] = X % 2;
				X = X / 2;
			}
		
			for (int j = 0; j < 32; j++){
		 		printf("%d", bit[j]);
			}
			printf("\n");	
		}

		// 負數（補數）
		else {
			for (int i = 31; i >= 0; i--){
                                bit[i] = X % 2;
                                X = X / 2;
                        }
			// 取反
			for (int j = 0; j < 32; j++){
				if (bit[j] == 0)
					bit[j] = 1;
				else
					bit[j] = 0;
			}

			// +1進位
			int x = 1;
			for (int k = 31; k >= 0; k--){
				int sum = bit[k] + x;
				bit[k] = sum % 2;
				x = sum / 2;
			}

			for (int l = 0; l < 32; l++){
				printf("%d", bit[l]);
			}
			printf("\n");
		}
	}

	// float
	if (N == 2){
		double X;
		scanf("%lf", &X);
		
		// S
		if (X > 0)
			bit[0] = 0;

		else {
			bit[0] = 1;
			X = -X;
		}
		// 正規化
		long long int_part = (long long)X;
		double fraction_part = X - int_part;

		
		int int_binary[64] = {};

		// count紀錄整數有幾位（從count+1開始）
		int int_count = 63;
		while(1){
			int_binary[int_count] = int_part % 2;
			int_part = int_part / 2;
			int_count--;

			if (int_part == 0)
				break;
		}
		
		int float_binary[64] = {};
		
		// count紀錄小數點到第幾位（到count-1）
		int float_count = 0;
		while(1){
			fraction_part = fraction_part * 2;
			float_binary[float_count] = (int)fraction_part;
			float_count++;
			fraction_part = fraction_part - (int)fraction_part;
			
			if (fraction_part == 0 || float_count > 64)
				break;	
		}

		int normalized[64] = {};
		int index = 0;
		int exp = 64 - int_count - 2;
			
		
		// 將正規化後的數字接起來存在新的array		
		for (int i = int_count + 1; i < 64; i++){
			normalized[index] = int_binary[i];
			index++;
		}
		for (int j = 0; j < float_count; j++){
			normalized[index] = float_binary[j];
			index++;
		}

		
		// E
		int num = exp + 127;
		
		for (int k = 8; k > 0; k--){
			bit[k] = num % 2;
			num = num / 2;
		}


		// F
		int x = 1;
		for (int y = 9; y < 32; y++){
			bit[y] = normalized[x];
			x++;
		}
		
		// output
		for (int a = 0; a < 32; a++){
			printf("%d", bit[a]);
		}
		printf("\n");
	}
	return 0;
	*/
}