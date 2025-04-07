#include <stdio.h>

int main(){
	long long a, b;
	scanf("%lld %lld", &a, &b);

	int condition = 0;
    if (a > 0){
		condition++;
	}
	if (b > 0){
		condition++;
	}
	
	// 如果一正一負直接加
	if (condition == 1){
		long long result;
		result = a + b;
		printf("%lld\n", result);		
	}
	
	// 如果都是正數則用unsgined long long
	if (a > 0 && b > 0){
		unsigned long long result;
		result = a + b;
		printf("%llu\n", result);
	}

	// 如果都是負數則轉成正數相加，輸出時加上負號
	if (a < 0 && b < 0){
		
		// 特殊例子
		if(a <= -9223372036854775807LL - 1 && b <= -9223372036854775807LL - 1){
			printf("-18446744073709551616\n");
		}
		
		else {
			a = -a;
			b = -b;
			unsigned long long result;
			result = a + b;
			printf("%llu\n", -result);
		}
	}	
}