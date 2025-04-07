#include <stdio.h>
#include <stdlib.h>

/*
將一個linked list 拆成兩個分別裝單數和雙數的linked list
*/

struct node {
    int value;             
    struct node *next; 
};

// 刪除linked list中是奇數的node
struct node *delete_odd(struct node *list){
    struct node *cur = list, *prev = NULL;
    while (cur != NULL){
        if (cur->value % 2 != 0){
            struct node *delete = cur;
            if (prev == NULL)
                list = cur->next;
            else
                prev->next = cur->next;
            cur = cur->next;
            free(delete);
        }
        else {
            prev = cur;
            cur = cur->next;
        }
    }
    return list;
}

// 刪除linked list中是偶數的node
struct node *delete_even(struct node *list){
    struct node *cur = list, *prev = NULL;
    while (cur != NULL){
        if (cur->value % 2 != 1){
            struct node *delete = cur;
            if (prev == NULL)
                list = cur->next;
            else
                prev->next = cur->next;
            cur = cur->next;
            free(delete);
        }
        else {
            prev = cur;
            cur = cur->next;
        }
    }
    return list;
}

// 加入data到linked list
struct node *add_to_list(struct node *list, int value) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;
    new_node->next = NULL;

    if (list == NULL) {
        return new_node;
    }

    struct node *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = new_node;
    return list;
}

// 複製linked list
struct node *copy_list(struct node *list) {
    struct node *copyed_list = NULL, *tail = NULL;
    while (list != NULL) {     
        struct node *new_node = malloc(sizeof(struct node));
        new_node->value = list->value; 
        new_node->next = NULL;

        if (copyed_list == NULL) {
            copyed_list = new_node;
            tail = new_node;
        } else {      
            tail->next = new_node;
            tail = new_node;
        }
        list = list->next; 
    }

    return copyed_list;
}

// 輸出linked list
void print_list(struct node *list) {
    struct node *cur = list;
    while (cur != NULL) {
        printf("%d -> ", cur->value);
        cur = cur->next;
    }
    printf("NULL\n");
}

// 釋放記憶體
void free_list(struct node *list) {
    struct node *cur;
    while (list != NULL) {
        cur = list;
        list = list->next;
        free(cur);
    }
}

int main(){
    struct node *list = NULL;
    struct node *odd_list = NULL;
    struct node *even_list = NULL;

    // 初始化鏈結串列：1 -> 2 -> 3 -> 4 -> 5 -> NULL
    list = add_to_list(list, 1);
    list = add_to_list(list, 2);
    list = add_to_list(list, 3);
    list = add_to_list(list, 4);
    list = add_to_list(list, 5);

    printf("linked list: ");
    print_list(list);

    // 要複製linked list是因為function會直接改動原始linked
    struct node *copy_list1 = copy_list(list);
    struct node *copy_list2 = copy_list(list);

    odd_list = delete_even(copy_list1);
    printf("Odd linked list: ");
    print_list(odd_list);

    even_list = delete_odd(copy_list2);
    printf("even linked list: ");
    print_list(even_list);

    free_list(odd_list);
    free_list(even_list);

    return 0;
}