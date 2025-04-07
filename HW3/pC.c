#include <stdio.h>

int main(){
	int a, b, c;
	scanf("%d-%d-%d", &a, &b, &c);
	
	// 用變數紀錄
	int answer = 0;
	
	if (a < b){
		answer = answer + 50;
	}
	if ((a + b) < c){
		answer = answer + 150;
	}
	if (a == c){
		answer = answer + 100;
	}
	if (a == c && a == b){
		answer = answer + 300;
	}
	printf("%d\n", answer);
	return 0;
}