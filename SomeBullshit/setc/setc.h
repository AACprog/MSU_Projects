#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define TABLE_SIZE 100


typedef struct Node {
    void* value;
    struct Node* next;
} Node;


typedef struct HashSet {
    Node** table;
    size_t element_size;
    unsigned int (*hashFunc)(void*);
    bool (*equalsFunc)(void*, void*);
} HashSet;


bool equalsInt(void* a, void* b) {
    return *(int*)a == *(int*)b;
}


HashSet* createHashSet(
    size_t element_size, 
    unsigned int (*hashFunc)(void*), 
    bool (*equalsFunc)(void*, void*)
) {
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    set->table = (Node**)malloc(TABLE_SIZE * sizeof(Node*));
    for (int i = 0; i < TABLE_SIZE; i++) {
        set->table[i] = NULL;
    }
    set->element_size = element_size;
    set->hashFunc = hashFunc;
    set->equalsFunc = equalsFunc;
    return set;
}


void add(HashSet* set, void* value) {
    unsigned int index = set->hashFunc(value);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = malloc(set->element_size);
    memcpy(newNode->value, value, set->element_size);
    newNode->next = NULL;

    Node* current = set->table[index];
    while (current != NULL) {
        if (set->equalsFunc(current->value, newNode->value)) {
            free(newNode->value);
            free(newNode);
            return;
        }
        current = current->next;
    }

    newNode->next = set->table[index];
    set->table[index] = newNode;
}


void removeValue(HashSet* set, void* value) {
    unsigned int index = set->hashFunc(value);
    Node* current = set->table[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (set->equalsFunc(current->value, value)) {
            if (prev == NULL) {
                set->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}


bool contains(HashSet* set, void* value) {
    unsigned int index = set->hashFunc(value);
    Node* current = set->table[index];

    while (current != NULL) {
        if (set->equalsFunc(current->value, value)) {
            return true;
        }
        current = current->next;
    }
    return false;
}


void freeHashSet(HashSet* set) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = set->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp->value);
            free(temp);
        }
    }
    free(set->table);
    free(set);
}
