#include "tuplec.h"

int main() {
    MultiTuple multiTuple = createMultiTuple(3);
    
    multiTuple.tuples[0] = createIntTuple(42);
    multiTuple.tuples[1] = createFloatTuple(3.14);
    multiTuple.tuples[2] = createStringTuple("Hello, World!");

    printMultiTuple(multiTuple);
    int tmp = multiTuple.tuples[0].value.intValue;
    printf("i = %d\n", tmp);
    freeMultiTuple(&multiTuple);

    return 0;
}
