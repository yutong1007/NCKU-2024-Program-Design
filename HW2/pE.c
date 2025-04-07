#include <stdio.h>

int main(){
	long long nums[5];
	for (int i = 0; i < 5; i++){
		// %*[^0-9] 代表不要scanf0-9以外的
		scanf("%*[^0-9]%lld", &nums[i]);
	}

	for (int j = 0; j < 4; j++){
		// 要加\在"前才可以輸出"
		printf("\"%lld\" ", nums[j]);
	}
	printf("\"%lld\"\n", nums[4]);
	return 0;
}