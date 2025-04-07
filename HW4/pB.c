#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main(){
	int N;
	scanf("%d", &N);
	
	// float的pointer 指向int N的32 bit binary 的記憶體位置
	float *i;
	i = (float*) &N;

	// 指標的值就是用int N的32 bit binary當作float type 32 bit binary輸出
	// *i是該point指向位置處存的值（該位置是int的 32 bit binary，但是用float的pointer指向，轉成float的方式解讀）
	printf("%.23e\n", *i);
	return 0;

	/*
	手刻轉換（但是有bug還沒解決QQ）
	int N;
	scanf("%d", &N);

	int bit[size] = {};	
	// 正數
	if (N > 0){
		for (int i = 31; i >= 0; i--){
			bit[i] = N % 2;
			N = N / 2;
		}
	}
	// 負數（補數）
	else {
		for (int i = 31; i >= 0; i--){
			bit[i] = N % 2;
			N = N / 2;
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
	}
	
	int exp = 0;
	for (int i = 1; i < 9; i++){
		if (bit[i] == 1){
			int x = 1;
			for (int j = 0; j < 8 -i; j++){
				x = x * 2;
			}
		exp = exp + x;
		}
	}
	exp = exp - 127;
	
	float fraction = 1.0;
	float weight = 0.5;
	for (int k = 9; k < 32; k++){
		if (bit[k] == 1){
			fraction = fraction + weight;	
		}
		weight = weight / 2;
	}
	

	printf("%lf\n", fraction);
	printf("%d\n", exp);

	float output = 1.0 * fraction;
	
	if (exp > 0){
		for (int a = 0; a < exp; a++){
			output = output * 2.0;
		}
	}
	else {
		for (int a = exp; a < 0; a++){
			output = output / 2.0;
		}
	}

	if (bit[0] == 1)
		output = -output;
	printf("%.23e\n", output);
	*/
}