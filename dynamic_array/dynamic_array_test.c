#include "dynamic_array.h"
#include "assert.h"
#include "stdio.h"

int main() {
    DArray *array = da_new(0);

    for (int i = 0; i <= 10; i++)
        da_add(array, i);

    assert(array->cap == 13);
    assert(array->size == 11);

    for (int i = 0; i < array->size; i++)
        printf("[%d]: %d; ", i, array->array[i]);
    printf("\n");

    da_remove(array, 0);

    assert(array->cap == 13);
    assert(array->size == 10);

    for (int i = 0; i < array->size; i++)
        printf("[%d]: %d; ", i, array->array[i]);
    printf("\n");

    DItem item = da_remove(array, 5);

    assert(item == 6);
    assert(array->cap == 13);
    assert(array->size == 9);

    for (int i = 0; i < array->size; i++)
        printf("[%d]: %d; ", i, array->array[i]);
    printf("\n");

    da_insert(array, 6, 5);

    assert(da_get(array, 5) == 6);
    assert(array->cap == 13);
    assert(array->size == 10);

    for (int i = 0; i < array->size; i++)
        printf("[%d]: %d; ", i, array->array[i]);
    printf("\n");

    da_free(array);
}