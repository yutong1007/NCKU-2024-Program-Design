#include <stdio.h>
#include <stdlib.h>
/*
array勁量開在全域
int board[2001][2001];
int north_south_skyline[2001];
int east_west_skyline[2001];
*/
// array可以多開1，然後從index=1開始input

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	
	// 動態分配記憶體
	int **board = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++) {
		board[i] = (int *)malloc(m * sizeof(int));
	}

	for (int j = 0; j < n; j++) {
		for (int k = 0; k < m; k++) {
	    		scanf("%d", &board[j][k]);
		}
	}

	int *north_south_skyline = (int *)malloc(m * sizeof(int));
	int *east_west_skyline = (int *)malloc(n * sizeof(int));
	
	// 找east_west天際線
	for (int a = 0; a < n; a++) {
		int max1 = board[a][0];
		for (int b = 1; b < m; b++) {
	    	if (board[a][b] > max1)
			max1 = board[a][b];
		}
		east_west_skyline[a] = max1;
	}
	
	// 找north_south天際線
	for (int x = 0; x < m; x++) {
		int max2 = board[0][x];
		for (int y = 1; y < n; y++) {
	    	if (board[y][x] > max2)
			max2 = board[y][x];
		}
		north_south_skyline[x] = max2;
	}

	long long counts = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			// 每個都會有兩個天際線，取較小的後算差值
			int max_height;
	      		if (east_west_skyline[i] < north_south_skyline[j])
				max_height = east_west_skyline[i];
			else
				max_height = north_south_skyline[j];
	    		counts += max_height - board[i][j];
		}
	}
	printf("%lld\n", counts);
	
	// 釋放記憶體
	free(north_south_skyline);
	free(east_west_skyline);
	for (int i = 0; i < n; i++) {
		free(board[i]);
	}
	free(board);

	return 0;
}