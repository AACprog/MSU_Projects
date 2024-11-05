#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union {
    int intValue;
    float floatValue;
    char* stringValue;
} TupleValue;

typedef enum {
    INT,
    FLOAT,
    STRING
} TupleType;

typedef struct {
    TupleValue value;
    TupleType type;
} Tuple;

typedef struct {
    Tuple* tuples; 
    size_t size;
} MultiTuple;


Tuple createIntTuple(int value) {
    Tuple tuple;
    tuple.value.intValue = value;
    tuple.type = INT;
    return tuple;
}


Tuple createFloatTuple(float value) {
    Tuple tuple;
    tuple.value.floatValue = value;
    tuple.type = FLOAT;
    return tuple;
}


Tuple createStringTuple(const char* value) {
    Tuple tuple;
    tuple.value.stringValue = malloc(strlen(value) + 1);
    strcpy(tuple.value.stringValue, value);
    tuple.type = STRING;
    return tuple;
}


void freeTuple(Tuple* tuple) {
    if (tuple->type == STRING) {
        free(tuple->value.stringValue);
    }
}


void printTuple(Tuple tuple) {
    switch (tuple.type) {
        case INT:
            printf("Tuple Value: %d (int)\n", tuple.value.intValue);
            break;
        case FLOAT:
            printf("Tuple Value: %.2f (float)\n", tuple.value.floatValue);
            break;
        case STRING:
            printf("Tuple Value: %s (string)\n", tuple.value.stringValue);
            break;
    }
}


MultiTuple createMultiTuple(size_t size) {
    MultiTuple multiTuple;
    multiTuple.tuples = malloc(size * sizeof(Tuple));
    multiTuple.size = size;
    return multiTuple;
}


void freeMultiTuple(MultiTuple* multiTuple) {
    for (size_t i = 0; i < multiTuple->size; ++i) {
        freeTuple(&multiTuple->tuples[i]);
    }
    free(multiTuple->tuples);
}


void printMultiTuple(MultiTuple multiTuple) {
    for (size_t i = 0; i < multiTuple.size; ++i) {
        printTuple(multiTuple.tuples[i]);
    }
}
