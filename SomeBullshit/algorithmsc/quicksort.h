#pragma once

#include "libsinclude.h"

void swap(void *a, void *b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}


int partition(void *base, size_t size, int (*cmp)(const void *, const void *), int low, int high) {
    char *arr = (char *)base;
    char *pivot = arr + high * size;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (cmp(arr + j * size, pivot) <= 0) {
            i++;
            swap(arr + i * size, arr + j * size, size);
        }
    }
    swap(arr + (i + 1) * size, arr + high * size, size);
    return i + 1;
}


void quicksort(void *base, size_t size, int (*cmp)(const void *, const void *), int low, int high) {
    if (low < high) {
        int pi = partition(base, size, cmp, low, high);
        quicksort(base, size, cmp, low, pi - 1);
        quicksort(base, size, cmp, pi + 1, high);
    }
}
