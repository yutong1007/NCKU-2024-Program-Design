#include <stdio.h>

int main(){
	long long a, b;
	scanf("%lld %lld", &a, &b);

	// 先確認a b是否相同正負
	int condition = 0;
	if (a > 0){
		condition++;
	}
	if (b > 0){
		condition++;
	}
	if (condition == 1){
		printf("No\n");
		return 0;
	}

	// 判斷是否overflow
	long long out = 9223372036854775807;
	
	
	if (a > 0 && b > 0){
		int gap = out - a;
		if (b > gap){
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}
	else {
		a = -a;
		b = -b;
		int gap = out - a;
		if (b > gap){
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}
	return 0;
}