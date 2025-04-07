#include <stdio.h>

int main(){
	int n, q, k;
	scanf("%d %d %d", &n, &q, &k);
	int passengers[n];
	for (int i = 0; i < n; i++){
		scanf("%d", &passengers[i]);
	}
	// array處存每次的結果，每次給定一個範圍，找這個範圍內有幾台車的乘客<k
	int queries[q];
	for (int j = 0; j < q; j++){
		int l, r;
		scanf("%d %d", &l, &r);
		int counts = 0;
		
		// 依照給的range查看有幾台車<k
		for (int a = l -1; a < r; a++){
			if (passengers[a] < k)
				counts++;
		}
		queries[j] = counts;	
	}

	for (int b = 0; b < q; b++){
		printf("%d\n", queries[b]);
	}
	return 0;
}