#include <stdio.h>

int main() {
    int a, b;
    char operator;
    scanf("%d%c%d", &a, &operator, &b);
    
    int ans;
    // operator是+的話為1 不是的話為0 
    ans  = (a + b)*(operator == '+') + (a - b)*(operator == '-') + (a * b)*(operator == '*');
    printf("%d\n", ans);
    return 0;
}
