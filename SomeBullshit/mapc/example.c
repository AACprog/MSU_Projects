#include "hashmapc.h"


int main() {
    HashMap* hashmap = create_hashmap();
    int apple_key = 1;
    int apple_value = 10;
    hashmap_insert(hashmap, &apple_key, sizeof(int), &apple_value, sizeof(int));


    const char* banana_key = "banana";
    double banana_value = 20.5;
    hashmap_insert(hashmap, (void*)banana_key, strlen(banana_key) + 1, &banana_value, sizeof(double));


    struct {
        int id;
    } orange_key = { 2 };
    char* orange_value = "Orange Juice";
    hashmap_insert(hashmap, &orange_key, sizeof(orange_key), orange_value, strlen(orange_value) + 1);


    size_t value_size;


    int* apple = (int*)hashmap_get(hashmap, &apple_key, sizeof(int), &value_size);
    if (apple) {
        printf("Value for key %d (apple): %d\n", apple_key, *apple);
    } else {
        printf("Key %d (apple) not found.\n", apple_key);
    }


    double* banana = (double*)hashmap_get(hashmap, (void*)banana_key, strlen(banana_key) + 1, &value_size);
    if (banana) {
        printf("Value for key '%s' (banana): %.1f\n", banana_key, *banana);
    } else {
        printf("Key '%s' (banana) not found.\n", banana_key);
    }


    struct {
        int id;
    } search_orange_key = { 2 };
    char* orange = (char*)hashmap_get(hashmap, &search_orange_key, sizeof(search_orange_key), &value_size);
    if (orange) {
        printf("Value for key { id: %d } (orange): %s\n", search_orange_key.id, orange);
    } else {
        printf("Key { id: %d } (orange) not found.\n", search_orange_key.id);
    }


    hashmap_free(hashmap);
    return 0;
}
