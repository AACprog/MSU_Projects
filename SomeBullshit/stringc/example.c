#include "stringc.h"


int main() {
    String str1 = createString("Hello");
    String str2 = createString(", World!");

    printString(&str1);
    printString(&str2);

    String concatenated = concatStrings(&str1, &str2);
    printString(&concatenated);

    destroyString(&str1);
    destroyString(&str2);
    destroyString(&concatenated);

    return 0;
}
