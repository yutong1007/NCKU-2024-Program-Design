#include <stdio.h>

int main(){
        long long a, b;
        scanf("%lld %lld", &a, &b);

        // 算有幾位數
        int Num =  a / 10;
        int digits = 1;

        while (Num > 0){
                Num = Num / 10;
                digits++;
        }
	int a_digits = digits;


	// 每一位數依序倒轉
        int reserved_a = 0;
        for (digits; digits > 0; digits--){
                int x = a % 10;
                a = a / 10;
                for (int i = 0; i < digits - 1; i++){
                        x = x * 10;
                }
                reserved_a = reserved_a + x;
        }
		
	// 將b乘上a的位數（才可以將a接在b後面）
	for (a_digits; a_digits > 0; a_digits--){
		b = b * 10;
	}
	printf("%lld\n", b + reserved_a);
        return 0;
}