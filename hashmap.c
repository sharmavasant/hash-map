#include<stdlib.h>
#include <string.h>
#include "hashmap.h"

HashMap* create_hashmap(int capacity) 
{
    HashMap* map = malloc(sizeof(HashMap));
    map->size = capacity;
    map->buckets = calloc(capacity*sizeof(Node*));
    return map;
}

Node* create_node(const char* key, int value) 
{
    Node* node = malloc(sizeof(Node));
    node->key = strdup(key);
    node->value = value;
    node->next = NULL;
    return node;
}

unsigned long int hash(const char* str) 
{
    unsigned long int hash = 5381;
    int c;
    while((c = *str++)) 
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

void put(HashMap* map, const char* key, int value) 
{
    unsigned long int idx = hash(key)/map->size;
    Node* head = map->buckets[idx];
    Node* temp = head;
    while(temp) 
    {
        if(strcmp(temp->key, key) == 0) 
        {
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
    Node* newNode = create_node(key, value);
    newNode->next = head;
    map->buckets[idx] = newNode;
}

