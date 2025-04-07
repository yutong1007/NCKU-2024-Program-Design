#include <stdio.h>

int main(){
	int N;
	scanf("%d", &N);

	// 算有幾位數
	int Num =  N / 10;
	int digits = 1;
	
	while (Num > 0){
		Num = Num / 10;
		digits++;
	}
	
	// 每一位數依序倒轉
	int reserved_N;
	for (digits; digits > 0; digits--){
		// x = 該位數的數字（從最小的位數開始）
		int x = N % 10;
		N = N / 10;

		// x要變成相對應的位數（可以用pow）
		for (int i = 0; i < digits - 1; i++){
			x = x * 10;
		}
		reserved_N = reserved_N + x;
	}
	printf("%d\n", reserved_N);
	return 0;
}