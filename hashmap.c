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
    unsigned long int idx = hash(key)%map->size;
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

int get(HashMap* map, const char* key, int* found) 
{
    unsigned long int idx = hash(key)%map->size;
    Node* head = map->buckets[idx];
    Node* temp = head;
    while(temp) 
    {
        if(strcmp(temp->key, key) == 0) 
        {
            *found = 1;
            return temp->value;
        }
        temp = temp->next;
    }
    *found = 0;
    return 0;
}

void remove_key(HashMap* map, const char* key) 
{
    unsigned long int idx = hash(key)%map->size;
    Node* head = map->buckets[idx];
    Node* temp = head;
    Node* prev = NULL;
    while(temp) 
    {
        if(strcmp(temp->key, key) == 0) 
        {
            if(prev) prev->next = temp->next;
            else map->buckets[idx] = temp->next;
            free(temp->key);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void free_hashmap(HashMap* map) 
{
    for(int i=0;i<map->size;i++) 
    {
        Node* node = map->buckets[i];
        while(node) 
        {
            Node* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}
