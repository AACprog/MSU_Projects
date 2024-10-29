#include "header.h"

int task(const char* filename) {
    int element;
    unsigned short int res = 0;
    FILE* file = fopen(filename, "r");
    if (file == NULL) return -1;
    while (fscanf(file, "%d", &element) == 1) {
        switch (element)
        {
            case 0: res = 10000 + res % 10000; break;
            case 1: res = res / 10000 * 10000 + 1000 + res % 1000; break;
            case 2: res = res / 1000 * 1000+ 100 + res % 100; break;
            case 3: res = res / 100 * 100 + 10 + res % 10; break;
            case 4: res = res / 10 * 10+ 1; break;
            default: break;
        }
    } 
    if (!feof(file)) {
        printf("The file wasn't read to the end\n");
    }
    fclose(file);
    
    return (int)(
        res / 10000 + 
        (res % 10000) / 1000 +
        (res % 1000) / 100 +
        (res % 100) / 10 +
        res % 10
    );
}
