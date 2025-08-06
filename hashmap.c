#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct KeyValuePair {
    char key[100];
    int value;
    struct KeyValuePair* next;
} KeyValuePair;

typedef struct HashMap {
    KeyValuePair* table[TABLE_SIZE];
} HashMap;

unsigned int hash(char* key) {
    unsigned int hashValue = 0;
    int c;
    while ((c = *key++)) {
        hashValue = (hashValue << 5) + c;
    }
    return hashValue % TABLE_SIZE;
}

void initHashMap(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
}

void insert(HashMap* map, char* key, int value) {
    unsigned int index = hash(key);
    KeyValuePair* newPair = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    strcpy(newPair->key, key);
    newPair->value = value;
    newPair->next = map->table[index];
    map->table[index] = newPair;
}

int get(HashMap* map, char* key) {
    unsigned int index = hash(key);
    KeyValuePair* current = map->table[index];
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    
    printf("Key not found!\n");
    return -1;
}

void removeKey(HashMap* map, char* key) {
    unsigned int index = hash(key);
    KeyValuePair* current = map->table[index];
    KeyValuePair* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                map->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Key not found!\n");
}

void freeHashMap(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        KeyValuePair* current = map->table[i];
        while (current != NULL) {
            KeyValuePair* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    HashMap map;
    initHashMap(&map);

    insert(&map, "apple", 10);
    insert(&map, "banana", 20);
    insert(&map, "cherry", 30);

    printf("apple: %d\n", get(&map, "apple"));
    printf("banana: %d\n", get(&map, "banana"));
    printf("cherry: %d\n", get(&map, "cherry"));

    removeKey(&map, "banana");
    printf("banana after removal: %d\n", get(&map, "banana"));

    freeHashMap(&map);
    return 0;
}
