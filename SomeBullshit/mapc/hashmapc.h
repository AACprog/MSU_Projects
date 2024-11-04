#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct KeyValue {
    void* key;
    size_t key_size;
    void* value;
    size_t value_size;
    struct KeyValue* next;
} KeyValue;


typedef struct HashMap {
    KeyValue** table;
} HashMap;


unsigned int hash(const void* key, size_t key_size) {
    unsigned int hash_value = 0;
    const unsigned char* p = (const unsigned char*)key;
    for (size_t i = 0; i < key_size; i++) {
        hash_value = (hash_value << 5) + hash_value + p[i];
    }
    return hash_value % TABLE_SIZE;
}


HashMap* create_hashmap() {
    HashMap* hashmap = malloc(sizeof(HashMap));
    hashmap->table = malloc(sizeof(KeyValue*) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashmap->table[i] = NULL;
    }
    return hashmap;
}


int compare_keys(const void* key1, size_t key1_size, const void* key2, size_t key2_size) {
    if (key1_size != key2_size) {
        return 0;
    }
    return memcmp(key1, key2, key1_size) == 0;
}


void hashmap_insert(HashMap* hashmap, void* key, size_t key_size, void* value, size_t value_size) {
    unsigned int index = hash(key, key_size);
    KeyValue* new_entry = malloc(sizeof(KeyValue));
    new_entry->key = malloc(key_size);
    memcpy(new_entry->key, key, key_size);
    new_entry->key_size = key_size;
    new_entry->value = malloc(value_size);
    memcpy(new_entry->value, value, value_size);
    new_entry->value_size = value_size;
    new_entry->next = hashmap->table[index];
    hashmap->table[index] = new_entry;
}


void* hashmap_get(HashMap* hashmap, void* key, size_t key_size, size_t* value_size) {
    unsigned int index = hash(key, key_size);
    KeyValue* entry = hashmap->table[index];
    while (entry != NULL) {
        if (compare_keys(entry->key, entry->key_size, key, key_size)) {
            *value_size = entry->value_size;
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL; 
}


void hashmap_free(HashMap* hashmap) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        KeyValue* entry = hashmap->table[i];
        while (entry != NULL) {
            KeyValue* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(hashmap->table);
    free(hashmap);
}
