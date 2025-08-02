#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// 哈希表节点结构
typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

// 哈希表结构
typedef struct HashTable {
    Node** buckets;
    int size;
} HashTable;

// 哈希函数
unsigned int hash(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

// 创建哈希表
HashTable* createHashTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = TABLE_SIZE;
    table->buckets = (Node**)calloc(TABLE_SIZE, sizeof(Node*));
    return table;
}

// 插入键值对
void insert(HashTable* table, const char* key, int value) {
    unsigned int index = hash(key);
    
    // 创建新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = NULL;
    
    // 如果桶为空，直接插入
    if (table->buckets[index] == NULL) {
        table->buckets[index] = newNode;
        return;
    }
    
    // 处理冲突：遍历链表
    Node* current = table->buckets[index];
    Node* prev = NULL;
    
    while (current != NULL) {
        // 如果键已存在，更新值
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            free(newNode->key);
            free(newNode);
            return;
        }
        prev = current;
        current = current->next;
    }
    
    // 插入到链表末尾
    prev->next = newNode;
}

// 查找键
int* search(HashTable* table, const char* key) {
    unsigned int index = hash(key);
    Node* current = table->buckets[index];
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return &current->value;
        }
        current = current->next;
    }
    
    return NULL;
}

// 删除键
void delete(HashTable* table, const char* key) {
    unsigned int index = hash(key);
    Node* current = table->buckets[index];
    Node* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                table->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// 释放哈希表
void freeHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        Node* current = table->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

// 示例用法
int main() {
    HashTable* table = createHashTable();
    
    // 插入示例数据
    insert(table, "apple", 5);
    insert(table, "banana", 8);
    insert(table, "orange", 3);
    
    // 查找
    int* value = search(table, "apple");
    if (value) {
        printf("apple: %d\n", *value);
    }
    
    // 删除
    delete(table, "banana");
    
    // 验证删除
    value = search(table, "banana");
    if (!value) {
        printf("banana not found\n");
    }
    
    // 释放内存
    freeHashTable(table);
    return 0;
}
