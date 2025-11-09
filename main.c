#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

int main() 
{
    HashMap* map = create_hashmap(10);
    put(map, "name", 100);
    put(map, "age", 25);
    put(map, "roll", 42);

    int found;
    int val = get(map, "age", &found);
    if (found) printf("age = %d\n", val);
    else printf("Not found\n");

    remove_key(map, "age");

    val = get(map, "age", &found);
    if (found) printf("age = %d\n", val);
    else printf("Not found\n");

    free_hashmap(map);

    return 0;
}