#pragma once

#include "libsinclude.h"


void forEach(void *arr, size_t size, size_t elementSize, void (*func)(void *)) {
    for (size_t i = 0; i < size; i++) {
        func((char *)arr + i * elementSize);
    }
}


int any(void *arr, size_t size, size_t elementSize, int (*func)(const void *)) {
    for (size_t i = 0; i < size; i++) {
        if (func((char *)arr + i * elementSize)) {
            return 1;
        }
    }
    return 0;
}


int all(void *arr, size_t size, size_t elementSize, int (*func)(const void *)) {
    for (size_t i = 0; i < size; i++) {
        if (!func((char*)arr + i * elementSize)) {
            return 0;
        }
    }
    return 1;
}


int findIndex(void *arr, size_t size, void* element, size_t elementSize) {
    for (size_t i = 0; i < size; i++) {
        if (memcmp(((char*)arr + i * elementSize), (char*)element + elementSize, elementSize)) {
            return i;
        }
    }
    return -1;
}


