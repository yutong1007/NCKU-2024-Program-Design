#include <stdio.h>

int main(){
	int N;
	scanf("%d", &N);
	
	int arr[N];
	for (int i = 0; i < N; i++){
		scanf("%d", &arr[i]);
	}
	int index = 0;
	int count = 0;
	
	while (1){

		// 超過array大小 break
		if (index >= N){
			break;
		}

		// 如果S <= 60，持續找到S > 60 或是array結束，然後count+1
		if (arr[index] <= 60){
			index++;
			if (arr[index] > 60 || !arr[index]){
				index++;
				count++;
			}
		}

		// 如果不再區間內，直接index + 1跳過
		else {
			index++;
		}
	}
	printf("%d\n", count);
	return 0;
}