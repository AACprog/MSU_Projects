#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **data;
    size_t size;      
    size_t capacity;  

} Vector;

Vector* create_vector(size_t initial_capacity) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->size = 0;
    vec->capacity = initial_capacity;
    vec->data = (void **)malloc(initial_capacity * sizeof(void *));
    return vec;
}


void free_vector(Vector *vec) {
    for (size_t i = 0; i < vec->size; i++) {
        free(vec->data[i]); 
    }
    free(vec->data);
    free(vec);
}


void resize_vector(Vector *vec, size_t new_capacity) {
    vec->capacity = new_capacity;
    vec->data = (void **)realloc(vec->data, new_capacity * sizeof(void *));
}


void vector_push_back(Vector *vec, void *element, size_t element_size) {
    if (vec->size >= vec->capacity) {
        resize_vector(vec, vec->capacity * 2);
    }
    vec->data[vec->size] = malloc(element_size); 
    memcpy(vec->data[vec->size], element, element_size);
    vec->size++;
}


void* vector_get(Vector *vec, size_t index) {
    if (index < vec->size) {
        return vec->data[index];
    }
    return NULL; 
}


size_t vector_size(Vector *vec) {
    return vec->size;
}
