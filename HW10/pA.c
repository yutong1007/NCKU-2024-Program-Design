#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct prefix {
    unsigned ip; 
    unsigned char len; 
    struct prefix* next;
};

typedef struct prefix Prefix;

int prefixlength[33] = {0};
int groups[256] = {0};
bool found[90000];
unsigned long long int begin, end;

/* arm 不支援 x86 的 rdtsc
inline unsigned long long int rdtsc()//32-bit
{
	unsigned long long int x;
	asm   volatile ("rdtsc" : "=A" (x));
	return x;
}
*/
#define CPU_FREQ 3200000000ULL
#define TIMER_FREQ 24000000ULL
uint64_t read_cntvct(){
    uint64_t cntvct;
    asm volatile("mrs %0, cntvct_el0" : "=r"(cntvct));
    return cntvct;
}

// task 1
void input(Prefix* head[256], char* s) {
    FILE* file = fopen(s, "r");
    if (file == NULL) {
        printf("FAIL to open file\n");
        return;
    }

    int j;
    unsigned ip1, ip2, ip3, ip4;
    unsigned char len;
    int debugCount = 1;
    Prefix* current[256] = {NULL};

    for (int i = 0; i < 256; i++) {
        current[i] = head[i];
    }

    while (debugCount <= 84633) {
        j = fscanf(file, "%u.%u.%u.%u/%hhu\n", &ip1, &ip2, &ip3, &ip4, &len);
        if (j != 5) {
            continue;
        }

        unsigned ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;

        Prefix* new = (Prefix*)malloc(sizeof(Prefix));
        new->ip = ip;
        new->len = len;
        new->next = NULL;

        unsigned pre = ip >> 24;
        if (head[pre] == NULL) {
            head[pre] = new;
            current[pre] = new;
        } else {
            current[pre]->next = new;
            current[pre] = new;
        }

        if (len >= 8) {
            groups[pre]++;
        }
        prefixlength[len]++;
        debugCount++;
    }

    printf("The total number of prefixes in the input file is: %d\n", debugCount - 1);
    fclose(file);
}

void group_len(Prefix *head[256], Prefix *grouped_head[33]){
    // 初始化每個分組的鏈結串列頭指針
    for (int i = 0; i <= 32; i++) {
        grouped_head[i] = NULL;
    }

    // 遍歷所有 head[256]
    for (int i = 0; i < 256; i++) {
        Prefix *current = head[i];
        while (current != NULL) {
            unsigned len = current->len; // 獲取前綴長度

            // 創建新節點
            Prefix *new_node = (Prefix *)malloc(sizeof(Prefix));
            new_node->ip = current->ip;
            new_node->len = current->len;
            new_node->next = NULL;

            // 插入到對應的分組鏈結串列
            if (grouped_head[len] == NULL) {
                grouped_head[len] = new_node;
            } else {
                Prefix *temp = grouped_head[len];
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = new_node;
            }

            // 移動到下一個節點
            current = current->next;
        }
    }

    // 可選：輸出每個分組的數量，用於驗證
    for (int i = 0; i <= 32; i++) {
        int count = 0;
        Prefix *current = grouped_head[i];
        while (current != NULL) {
            count++;
            current = current->next;
        }
        printf("Number of prefixes with length %d: %d\n", i, count);
    }
}

void length_distribution() {
    for (int i = 0; i <= 32; i++) {
        printf("The number of prefixes with prefix length %d = %d\n", i, prefixlength[i]);
    }
}

// task 2
void segment(Prefix *grouped_head[33], Prefix *hash_table[33][256]){
    // 初始化 hash_table
    for (int len = 0; len <= 32; len++){
        for (int j = 0; j < 256; j++){
            hash_table[len][j] = NULL;
        }
    }

    // 迭代前面分組完的grouped_head
    for (int len = 0; len <= 32; len++){
        Prefix *current = grouped_head[len];
        while (current != NULL){
            unsigned msb_8_bits = current->ip >> 24;

            // 創建新節點
            Prefix *new_node = (Prefix *)malloc(sizeof(Prefix));
            new_node->ip = current->ip;
            new_node->len = current->len;
            new_node->next = NULL;

            // 插入到對應的 hash_table[len][msb_8_bits]
            if (hash_table[len][msb_8_bits] == NULL){
                hash_table[len][msb_8_bits] = new_node;
            } 
            else{
                Prefix *temp = hash_table[len][msb_8_bits];
                while (temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = new_node;
            }

            current = current->next;
        }
    }
}


void prefix_insert(Prefix *hash_table[33][256], char *s) {
    FILE *file, *insertfile;

    insertfile = fopen("clock_insert.csv", "w+");
    fprintf(insertfile, "clock cycles\n");
    unsigned long long int begin, end;

    file = fopen(s, "r");

    int j;
    unsigned ip1, ip2, ip3, ip4;
    unsigned char len;
    int debugCount = 1;

    while (debugCount <= 4455) {
        begin = read_cntvct();

        j = fscanf(file, "%u.%u.%u.%u/%hhu\n", &ip1, &ip2, &ip3, &ip4, &len);
        if (j != 5) {
            continue;
        }

        // 轉成32位元的IP
        unsigned ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
        
        // hash table index
        unsigned msb_8_bits = ip >> 24;

        // 新節點
        Prefix *new_node = (Prefix *)malloc(sizeof(Prefix));
        new_node->ip = ip;
        new_node->len = len;
        new_node->next = NULL;

        // 對應的hash table
        Prefix **bucket_head = &hash_table[len][msb_8_bits];
        
        // 按 IP 升序排列
        if (*bucket_head == NULL || ip < (*bucket_head)->ip){
            // 插入到linked list head
            new_node->next = *bucket_head;
            *bucket_head = new_node;
        } 
        else{
            // 找到插入點
            Prefix *current = *bucket_head;
            while (current->next != NULL && ip > current->next->ip){
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }

        end = read_cntvct();
        fprintf(insertfile, "%llu\n", (end-begin)*(CPU_FREQ/TIMER_FREQ));
        debugCount++;
    }

    fclose(file);
    fclose(insertfile);
}

void prefix_delete(Prefix *hash_table[33][256], char *s) {
    FILE *file, *deletefile;

    deletefile = fopen("clock_delete.csv", "w+");
    fprintf(deletefile, "clock cycles\n");
    unsigned long long int begin, end;

    file = fopen(s, "r");

    int j;
    unsigned ip1, ip2, ip3, ip4;
    unsigned char len;
    int debugCount = 1;

    while (debugCount <= 4163) {

        begin = read_cntvct();

        j = fscanf(file, "%u.%u.%u.%u/%hhu", &ip1, &ip2, &ip3, &ip4, &len);
        if (j != 5) {
            continue;
        }

        // 轉成32位元的IP
        unsigned ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;

        // hash table index
        unsigned msb_8_bits = ip >> 24;

        // 對應的hash table
        Prefix **bucket_head = &hash_table[len][msb_8_bits];

        // 初始化當前和前一個節點指針
        Prefix *current = *bucket_head;
        Prefix *prev = NULL;

        // 持續迭代linked list找要刪除的節點
        while (current != NULL && (current->ip != ip || current->len != len)) {
            prev = current;
            current = current->next;
        }

        // 如果找到節點
        if (current != NULL) {
            // 如果是head node
            if(prev == NULL){
                *bucket_head = current->next;
            } 
            else{
                prev->next = current->next;
            }
            free(current);
        }

        end = read_cntvct();
        fprintf(deletefile, "%llu\n", (end-begin)*(CPU_FREQ/TIMER_FREQ));
        debugCount++;
    }

    fclose(file);
    fclose(deletefile);
}

void search(Prefix *hash_table[33][256], char *s) {
    FILE *file, *searchfile;

    searchfile = fopen("clock_search.csv", "w+");
    fprintf(searchfile, "clock cycles\n");
    unsigned long long int begin, end;

    file = fopen(s, "r");

    int j;
    unsigned ip1, ip2, ip3, ip4;
    int debugCount = 1;

    while (debugCount <= 89088) {

        begin = read_cntvct();

        j = fscanf(file, "%u.%u.%u.%u", &ip1, &ip2, &ip3, &ip4);
        if (j != 4) {
            continue;
        }

        // 轉成32位元的IP
        unsigned ip = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
        unsigned msb_8_bits = ip >> 24;
        
        bool match_found = false;

        // prefix length由大到小進行match
        for (int len = 32; len >= 0; len--) {
            Prefix *current = hash_table[len][msb_8_bits];
            while (current != NULL) {
                unsigned mask = (len == 0) ? 0 : ~((1 << (32 - len)) - 1);
                if ((ip & mask) == (current->ip & mask)) {
                    match_found = true;
                    break;
                }
                current = current->next;
            }
            if (match_found) {
                break;
            }
        }

        // result
        if (match_found) {
            found[debugCount] = true;
        } else {
            found[debugCount] = false;
        }

        end = read_cntvct();
        fprintf(searchfile, "%llu\n", (end-begin)*(CPU_FREQ/TIMER_FREQ));
        debugCount++;
    }

    fclose(file);
    fclose(searchfile);
}


int main(int argc, char *argv[]) {

    printf("The file initializing the routing table: %s\n", argv[1]);
    printf("The file for extra insertion into the routing table: %s\n", argv[2]);
    printf("The file to delete specific IPs from the routing table: %s\n", argv[3]);
    printf("The file for IP lookups: %s\n", argv[4]);
    printf("\n");

    Prefix *prefixList[256] = {NULL};
    Prefix *grouped_head[33] = {NULL};
    Prefix *hash_table[33][256];
    input(prefixList, argv[1]);
    printf("\n");

    group_len(prefixList, grouped_head);
    length_distribution();

    segment(prefixList, hash_table);
    prefix_insert(hash_table, argv[2]);
    prefix_delete(hash_table, argv[3]);
    search(hash_table, argv[4]);

    for (int i = 0; i < 256; i++) {
        Prefix *current = prefixList[i];
        while (current != NULL) {
            Prefix *temp = current;
            current = current->next;
            free(temp);
        }
    }

    for (int len = 0; len <= 32; len++) { 
        for (int bucket = 0; bucket < 256; bucket++){ 
            Prefix *current = hash_table[len][bucket];
            while (current != NULL) {
                Prefix *temp = current;
                current = current->next;
                free(temp); 
            }
            hash_table[len][bucket] = NULL;
        }
    }
    return 0;
}