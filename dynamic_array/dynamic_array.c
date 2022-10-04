#include "dynamic_array.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

void *_da_malloc(DSize size) {
    void *mem = malloc(size);

    if (NULL == mem && size > 0)
        abort();

    return mem;
}

void _da_free(void *mem) {
    if (NULL != mem)
        free(mem);
}

DSize _da_new_capacity(DSize cap, DMethod method) {
    switch (method) {
        case METHOD_SINGLE:
            cap += 1;
            break;
        case METHOD_FACTOR:
            cap += cap >> 1;
            break;
    }

    return cap;
}

DArray *da_new(DSize cap) {
    if (cap == 0)
        cap = INITIAL_CAP;

    DArray *array = _da_malloc(sizeof(DArray));
    array->array = malloc(sizeof(DItem) * cap);
    array->size = 0;
    array->cap = cap;

    return array;
}

void da_free(DArray *array) {
    _da_free(array->array);
    _da_free(array);
}

void da_add(DArray *array, DItem item) {
    if (array->size >= array->cap) {
        DSize cap = _da_new_capacity(array->cap, METHOD_FACTOR);
        DItem *new_array = realloc(array->array, cap * sizeof(DItem));
        array->array = new_array;
        array->cap = cap;
    }

    array->array[array->size++] = item;
}

void da_insert(DArray *array, DItem item, DSize index) {
    if (array->size >= array->cap) {
        DSize cap = _da_new_capacity(array->cap, METHOD_FACTOR);
        DItem *new_array = realloc(array->array, cap * sizeof(DItem));
        array->array = new_array;
        array->cap = cap;
    }

    memmove(array->array + index + 1, array->array + index, (array->size++ - index) * sizeof(DItem));
    array->array[index] = item;
}

DItem da_remove(DArray *array, DSize index) {
    if (index >= array->size)
        return 0;

    DItem item = array->array[index];
    memmove(array->array + index, array->array + index + 1, (--array->size - index) * sizeof(DItem));

    return item;
}

DItem da_get(DArray *array, DSize index) {
    if (index >= array->size)
        return 0;

    return array->array[index];
}
