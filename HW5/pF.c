#include <stdio.h>
/*
用一個bool array去紀錄array中每台車的乘客是否<k（是=1/否=0）
最後用prefix_sum統計range中裡面有幾個1
*/

int main(){
	int n, q, k;
	scanf("%d %d %d", &n, &q, &k);
	int array[n];
	int bool_array[n];

	for (int i = 0; i < n; i++){
		scanf("%d", &array[i]);
		if (array[i] < k)
			bool_array[i] = 1;
		else
			bool_array[i] = 0;
	}
	int prefix_sum[n];
	prefix_sum[0] = bool_array[0];
	for (int j = 1; j < n; j++){
		prefix_sum[j] = bool_array[j] + prefix_sum[j-1];
	}
	
	int queries[q];
	for (int a = 0; a < q; a++){
		int l, r;
		scanf("%d %d", &l, &r);
		if (l == 0)
			queries[a] = prefix_sum[r-1];
		else
			queries[a] = prefix_sum[r-1] - prefix_sum[l-2];
	}

	for (int b = 0; b < q; b++){
		printf("%d\n", queries[b]);
	}
	return 0;
}