#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t length;
} String;

String createString(const char *initialData) {
    String str;
    str.length = strlen(initialData);
    str.data = (char *)malloc(str.length + 1);
    if (str.data) {
        strcpy(str.data, initialData);
    }
    return str;
}


void destroyString(String *str) {
    if (str->data) {
        free(str->data);
        str->data = NULL;
        str->length = 0;
    }
}


String concatStrings(const String *str1, const String *str2) {
    String result;
    result.length = str1->length + str2->length;
    result.data = (char *)malloc(result.length + 1);
    if (result.data) {
        strcpy(result.data, str1->data);
        strcat(result.data, str2->data);
    }
    return result;
}


void printString(const String *str) {
    if (str->data) {
        printf("%s\n", str->data);
    } else {
        printf("(null)\n");
    }
}
