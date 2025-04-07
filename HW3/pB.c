#include <stdio.h>
/*
用3個condition分別判斷有沒有出現該數字
最後依照condition狀態輸出對應結果
*/

int main(){
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	
	int condition_1 = 1, condition_2 = 1, condition_3 = 1;
	
	if (a != 1 && b != 1 && c!= 1){
		condition_1 = 0;
	}
	if (a != 2 && b != 2 && c!= 2){
		condition_2 = 0;
	}
	if (a != 3 && b != 3 && c!= 3){
		condition_3 = 0;
	}
	
	if (condition_1 == 1 && condition_2 == 1 && condition_3 == 1){
                printf("Oh, Fried Shrimp, you're amazing!\n");
		return 0;
        }

	if (condition_1 == 0)
		printf("1");
	
	if (condition_2 == 0 && condition_1 == 1)
		printf("2");
	if (condition_2 == 0 && condition_1 == 0)
		printf(" 2");
	if (condition_3 == 0 && condition_2 == 1)
		printf("3");
	if (condition_3 == 0 && condition_2 == 0)
		printf(" 3");
	printf("\n");
	return 0;
}