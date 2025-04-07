#include <stdio.h>

int main(){
	int m;
	scanf("%d", &m);
	
	int total;
	scanf("%d", &total);
	int counts = 1;
	
	while (total <= m){
		int k;
		// scanf會自動換行（會有\n）
		scanf("%d", &k);
		total = total + k;
		counts++;
	}
	printf("Fried Pork!!!!\n");
	printf("%d\n", counts);
	return 0;
}