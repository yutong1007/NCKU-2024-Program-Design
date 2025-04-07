#include <stdio.h>
#define Size 1000001
// 和pB一樣，只要改array大小

int main(){
	int N;
	scanf("%d", &N);
	int d[Size] = {};

	for (int i = 0; i < N; i++){
		int L, R;
		scanf("%d %d", &L, &R);
		d[L]++;
		d[R]--;
	}

	int max_vehicles = d[0];
	int current_vehicles = d[0];
	for (int j = 1; j < Size; j++){
		current_vehicles = current_vehicles + d[j];
		if (current_vehicles > max_vehicles)
			max_vehicles = current_vehicles;
	}
	printf("%d\n", max_vehicles);
	return 0;
}