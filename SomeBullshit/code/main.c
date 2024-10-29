#include "header.h"


int main(void) {
    char filename[100];
    int res;
    printf("Enter the filename: ");
    scanf("%s", filename);
    res = task(filename);
    switch (res) {
        case -1: printf("No file\n"); break;
        default: printf("Result %d\n", res); break;
    }
    return 0;
}