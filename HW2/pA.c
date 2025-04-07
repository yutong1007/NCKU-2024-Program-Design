#include <stdio.h>

int main(int argc, char *argv[]) {
    // argc是執行時輸入讀參數（檔名也算） argv是裝這些參數的ㄗ
    int num = argc - 1;
    printf("%d\n", num);
    return 0;
}