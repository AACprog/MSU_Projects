#include "vectorlibc.h"


int main() {
    Vector *int_vector = create_vector(2);
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    vector_push_back(int_vector, &value1, sizeof(int));
    vector_push_back(int_vector, &value2, sizeof(int));
    vector_push_back(int_vector, &value3, sizeof(int));
    for (size_t i = 0; i < vector_size(int_vector); i++) {
        int *value = (int *)vector_get(int_vector, i);
        printf("%d\n", *value);
    }
    free_vector(int_vector);


    Vector *double_vector = create_vector(1);
    double value4 = 10.0;
    double value5 = 20.0;
    double value6 = 30.0;
    vector_push_back(double_vector, &value4, sizeof(double));
    vector_push_back(double_vector, &value5, sizeof(double));
    vector_push_back(double_vector, &value6, sizeof(double));
    for (size_t i = 0; i < vector_size(double_vector); i++) {
        double *value = (double *)vector_get(double_vector, i);
        printf("%f\n", *value);
    }
    free_vector(double_vector);
    return 0;
}
