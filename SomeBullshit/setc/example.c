#include "setc.h"


unsigned int hashInt(void* value) {
    return *(int*)value % TABLE_SIZE;
}


int main() {
    HashSet* set = createHashSet(sizeof(int), hashInt, equalsInt);

    int a = 10, b = 20, c = 30;

    add(set, &a);
    add(set, &b);
    add(set, &c);

    printf("Contains 20: %s\n", contains(set, &b) ? "true" : "false");
    printf("Contains 40: %s\n", contains(set, &(int){40}) ? "true" : "false");

    removeValue(set, &b);
    printf("Contains 20: %s\n", contains(set, &b) ? "true" : "false");
    printf("Contains 30: %s\n", contains(set, &c) ? "true" : "false");

    freeHashSet(set);
    return 0;
}
