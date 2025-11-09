#ifndef __HASHMAP_H__

#define __HASHMAP_H__

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    int size;
    Node **buckets;
} HashMap;

HashMap* create_hashmap(int capacity);
Node* create_node(const char* key, int value);
unsigned long int hash(const char* str);
void put(HashMap* map, const char* key, int value);
#endif