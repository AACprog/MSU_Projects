#include <stdio.h>
#include "algorithmsc.h"


void printIntArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void printDoubleArray(double arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

int int_cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


int double_cmp(const void *a, const void *b) {
    return (*(double*)a - *(double*)b);
}


int is_even_int(const void *num) {
    int* a = (int*)num;
    if ((*a) % 2 == 0) return 1;
    return 0;
}


void doubling_int(void *num) {
    *(int *)num *= 2;
}


int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array: \n");
    printIntArray(arr, n);
    quicksort(arr, sizeof(int), int_cmp, 0, n - 1);
    printf("Sorted array: \n");
    printIntArray(arr, n);
    double arr2[] = {10.1, 30.3, 5.2323, 1, 7};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Original array: \n");
    printDoubleArray(arr2, n2);
    quicksort(arr2, sizeof(double), double_cmp, 0, n2 - 1);
    printDoubleArray(arr2, n2);


    int arr3[] = {1, 2, 3};
    int n3 = 3;
    printf("Original array: \n");
    printIntArray(arr3, 3);
    int res1 = all(arr3, n3, sizeof(int), is_even_int);
    int res2 = any(arr3, n3, sizeof(int), is_even_int);
    int el = 2;
    int index = findIndex(arr3, 3, &el, sizeof(int));
    printf("all: %d, any: %d, index: %d\n", res1, res2, index);
    forEach(arr3, 3, sizeof(int), doubling_int);
    printf("After doubling:\n");
    printIntArray(arr3, 3);
    return 0;
}