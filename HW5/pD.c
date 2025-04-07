#include <stdio.h>
/*
prefix_sum[i]存的是a1+...+到ai
prefix_sum[0] = a0
prefix_sum[1] = a0 + a1
prefix_sum[2] = a0 + a1 + a2
如果要求a3+...+a7 = prefix_sum[7] - prefix_sum[3-1]
a1+...+a7 - a1+...a2 = a3+...+a7
*/

int main(){
	// 改成long long就過了
	long long N;
	scanf("%lld", &N);
	
	long long array[N];
	for (int i = 0; i < N; i++){
		scanf("%lld", &array[i]);
	}

	long long prefix_sum[N];
	prefix_sum[0] = array[0];
	for (int j = 1; j < N; j++){
		prefix_sum[j] = array[j] + prefix_sum[j-1];
	}
	
	long long Q;
	scanf("%lld", &Q);
	long long sum_arr[Q];

	for(int l = 0; l < Q; l++){
		int L, R;
		scanf("%d %d", &L, &R);
		// 如果L = 1，代表直接加到R，不用扣要前面部分
		if (L == 1)
			sum_arr[l] = prefix_sum[R-1];
		else
			sum_arr[l] = prefix_sum[R-1] - prefix_sum[L-2];
	}

	for (int k = 0; k < Q; k++){
		printf("%lld\n", sum_arr[k]);
	}
	return 0;
}