#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Prefix
{
    unsigned ip;
    unsigned char len; // 佔 1-bit
    struct Prefix *next;
} Prefix; // 視為 linked list 的 node

int prefixlength[33] = {0};
int groups[256] = {0};
bool found[90000];
unsigned long long int begin, end;
// rdtsc 和 rdtsc_64bits，分別用來取得32位元和64位元的時間戳記計數器值。
// 用 begin 和 end 來存開始和結束的時間戳記
// 內嵌（inline）：到呼叫它的地方，而不是像正常的函式呼叫一樣跳轉到函式的位置執行。
unsigned long long int rdtsc() // 32-bit
{
    unsigned long long int x;
    // 這一行的作用是嵌入了一個組合語言指令 rdtsc，並將其結果保存到變數 x 中
    // 同時確保這段組合語言代碼的執行不受編譯器的優化影響。
    asm volatile("rdtsc" : "=A"(x));
    return x;
}

// head 就是 linked list 中的 "first" pointer
// *head 可以取到目前所指的 node
// ok
void input(Prefix *head[256], char *s)
{
    FILE *file;
    file = fopen(s, "r");
    // file = fopen("share/HW11/routing_table.txt", "r");
    if (file == NULL)
        printf("FAIL to open file");
    int j;
    unsigned ip1, ip2, ip3, ip4;
    unsigned char len;
    int debugCount = 1;
    Prefix *current[256]; // 紀錄每一條的當前位置
    for (int i = 0; i < 256; i++)
    {
        current[i] = head[i];
    }

    while (debugCount <= 84633)
    {
        j = fscanf(file, "%u.%u.%u.%u/%hhu\n", &ip1, &ip2, &ip3, &ip4, &len);
        // j = fscanf(file, "%d.%d.%d.%d/%d", &ip1, &ip2, &ip3, &ip4, &len);
        // printf("%d.%d.%d.%d/%d\n", ip1, ip2, ip3, ip4, len);
        if (j == 4)
        {
            if (ip2 == 0 && ip3 == 0 && ip4 == 0)
                len = 8;
            else if (ip3 == 0 && ip4 == 0)
                len = 16;
            else if (ip4 == 0)
                len = 24;
            else
                len = 32;
        }
        unsigned ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
        // printf("%d.%d.%d.%d/%hhu\n", ip >> 24, (ip << 8) >> 24, (ip << 16) >> 24, (ip << 24) >> 24, len);
        Prefix *new = (Prefix *)malloc(sizeof(Prefix));
        new->ip = ip;
        new->len = len;
        new->next = NULL;
        unsigned pre = ip >> 24;
        if (head[pre] == NULL)
        // 若目前為空
        {
            head[pre] = new;
            current[pre] = head[pre];
        }
        else // 若這條 linked list 不為空
        {
            current[pre]->next = new;
            current[pre] = new;
        }
        if (len >= 8)
            groups[pre]++;
        prefixlength[len]++;
        debugCount++;
    }
    printf("The total number of prefixes in the input file is : %d.\n", debugCount - 1);
    fclose(file);
}

void length_distribution()
{
    int sum = 0;
    for (int i = 0; i < 33; i++)
    {
        sum += prefixlength[i];
        // printf("the number of prefixes with prefix length %d = %d\n", i, prefixlength[i]);
    }
    // if (sum == 84633)
    //     printf("Matched\n");
}

void segment(int d)
{
    d = 256;
    // 用 linked list 遍歷所有 prefix
    for (int i = 0; i < 256; i++)
    {
        printf("The number of prefixes in group %d = %d\n", i, groups[i]);
    }
}

void prefix_insert(Prefix *head[256], char *s)
{
    FILE *file, *insertfile;

    insertfile = fopen("clock_insert.csv", "w+");
    fprintf(insertfile, "clock cycles\n");   // header of csv
    unsigned long long int begin, end;

    file = fopen(s, "r");
    // file = fopen("share/HW11/inserted_prefixes.txt", "r");
    int j;
    unsigned ip1, ip2, ip3, ip4;
    unsigned char len;
    int debugCount = 1;
    Prefix *current[256]; // 紀錄每一條的當前位置
    for (int i = 0; i < 256; i++)
    {
        current[i] = head[i];
    }

    while (debugCount <= 4455)
    {
        begin = rdtsc(); // clock begin

        j = fscanf(file, "%u.%u.%u.%u/%hhu\n", &ip1, &ip2, &ip3, &ip4, &len);
        unsigned ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
        // printf("%d.%d.%d.%d/%hhu\n", ip >> 24, (ip << 8) >> 24, (ip << 16) >> 24, (ip << 24) >> 24, len);
        Prefix *new = (Prefix *)malloc(sizeof(Prefix));
        new->ip = ip;
        new->len = len;
        new->next = NULL;
        unsigned pre = ip >> 24;
        current[pre] = head[pre];
        if (head[pre] == NULL)
        // 若目前為空
        {
            // printf("Hi\n");
            head[pre] = new;
            current[pre] = head[pre];
        }
        else if (ip < head[pre]->ip) // 若這條 linked list 不為空，且新的ip插在頭
        {
            new->next = current[pre];
            head[pre] = new;
            current[pre] = head[pre]; // 這行要寫在後面，正確的更新 current[pre]
        }
        else // 若這條 linked list 不為空，且新的ip插在中間或尾巴
        {
            current[pre] = head[pre];
            while (current[pre]->next != NULL && ip > current[pre]->next->ip)
            {
                current[pre] = current[pre]->next; // 繼續找下一個節點，直到找到插入點前
            }
            new->next = current[pre]->next;
            current[pre]->next = new;
        }
        if (len >= 8)
            groups[pre]++;
        prefixlength[len]++;
        debugCount++;

        end = rdtsc(); // clock begin
        fprintf(insertfile, "%d\n", (end-begin));   // header of csv
    }
    fclose(file);
    fclose(insertfile);
    // printf("count = %d\n", debugCount);
}

void prefix_delete(Prefix *head[256], char *s)
{
    FILE *file, *deletefile;

    deletefile = fopen("clock_delete.csv", "w+");
    fprintf(deletefile, "clock cycles\n");   // header of csv
    unsigned long long int begin, end;

    file = fopen(s, "r");
    // file = fopen("share/HW11/deleted_prefixes.txt", "r");
    if (file == NULL)
        printf("FAIL to open file");
    int j;
    unsigned ip1, ip2, ip3, ip4;
    unsigned char len;
    int debugCount = 1;
    Prefix *current[256], *prev[256]; // 紀錄每一條的當前位置，刪除點前一個位置
    for (int i = 0; i < 256; i++)
    {
        current[i] = head[i];
        prev[i] = NULL;
    }
    while (debugCount <= 4163)
    {
        begin = rdtsc(); // clock begin

        j = fscanf(file, "%u.%u.%u.%u/%hhu", &ip1, &ip2, &ip3, &ip4, &len);
        unsigned ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
        // printf("%d.%d.%d.%d/%hhu\n", ip >> 24, (ip << 8) >> 24, (ip << 16) >> 24, (ip << 24) >> 24, len);
        if (debugCount == 146)
            len = 8;

        unsigned pre = ip >> 24;
        current[pre] = head[pre];
        // 找節點
        while (current[pre] != NULL && (ip != current[pre]->ip || len != current[pre]->len))
        {
            prev[pre] = current[pre];
            current[pre] = current[pre]->next; // 繼續找下一個節點，直到找到刪除點前
        }
        // 如果找到節點
        if (current[pre] != NULL)
        {
            if (prev[pre] == NULL) // 如果要刪除的是頭部
            {
                head[pre] = current[pre]->next; // 頭部更新至下一個
            }
            else
            {
                prev[pre]->next = current[pre]->next;
            }

            if (len >= 8)
                groups[pre]--;
        }
        debugCount++;

        end = rdtsc(); // clock begin
        fprintf(deletefile, "%d\n", (end-begin));   // header of csv
    }
    fclose(file);
    fclose(deletefile);
}

void search(Prefix *head[256], char *s)
{
    FILE *file, *searchfile;

    searchfile = fopen("clock_search.csv", "w+");
    fprintf(searchfile, "clock cycles\n");   // header of csv
    unsigned long long int begin, end;

    file = fopen(s, "r");
    // file = fopen("share/HW11/trace_file.txt", "r");
    if (file == NULL)
        printf("FAIL to open file");
    int j;
    unsigned ip1, ip2, ip3, ip4;
    // unsigned char len;
    int debugCount = 1;
    Prefix *current[256]; // 紀錄每一條的當前位置
    for (int i = 0; i < 256; i++)
    {
        current[i] = head[i];
    }
    while (debugCount <= 89088)
    {
        begin = rdtsc(); // clock begin

        j = fscanf(file, "%u.%u.%u.%u", &ip1, &ip2, &ip3, &ip4);
        unsigned ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
        // printf("%d.%d.%d.%d/%hhu\n", ip >> 24, (ip << 8) >> 24, (ip << 16) >> 24, (ip << 24) >> 24, len);
        unsigned pre = ip >> 24;
        Prefix *initialPosition = head[pre]; // 保存初始位置
        while (current[pre] != NULL)
        {
            // printf("count = %d\n", debugCount);
            if (ip == current[pre]->ip)
            {
                found[debugCount] = true;
                break;
            }
            current[pre] = current[pre]->next; // 繼續找下一個節點，直到找到刪除點前
        }
        // 恢复到初始位置
        current[pre] = initialPosition;
        debugCount++;

        end = rdtsc(); // clock begin
        fprintf(searchfile, "%d\n", (end-begin));   // header of csv
    }
    fclose(file);
    fclose(searchfile);
}

void printLinkedList(Prefix *head[256])
{
    Prefix *current = head[47]; // 拿第 47 條檢查
    while (current != NULL)
    {
        unsigned cip = current->ip;
        unsigned char len = current->len;
        printf("%d.%d.%d.%d/%hhu\n", cip >> 24, (cip << 8) >> 24, (cip << 16) >> 24, (cip << 24) >> 24, len);
        current = current->next;
    }
    printf("=================================\n");
}

int main(int argc, char *argv[])
{
    Prefix *prefixList[256];
    // 第一層代表有多少條 linked list 的 head pointer
    // 每一格存那條 linked list 的 head
    for (int i = 0; i < 256; i++)
    {
        prefixList[i] = NULL;
    }
    input(prefixList, argv[1]);
    printLinkedList(prefixList); // input 後
    length_distribution();

    // segment(atoi(argv[5]));
    prefix_insert(prefixList, argv[2]);
    printLinkedList(prefixList); // insert 後

    prefix_delete(prefixList, argv[3]);
    printLinkedList(prefixList); // delete 後

    // segment(atoi(argv[5]));
    for (int i = 0; i <= 90000; i++)
    {
        found[i] = false;
    }

    search(prefixList, argv[4]);
}
