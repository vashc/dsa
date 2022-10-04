#pragma once
#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

// Possible reallocation methods
#define METHOD_SINGLE 0
#define METHOD_FACTOR 1

#define INITIAL_CAP 4

#define MAX(x, y) ((x) >= (y) ? (x) : (y))

typedef int DItem;
typedef unsigned int DSize;
typedef unsigned int DMethod;

typedef struct DArray {
    DItem *array;
    DSize size;
    DSize cap;
} DArray;

// Public methods
DArray *da_new(DSize cap);

void da_free(DArray *array);

void da_add(DArray *array, DItem item);

void da_insert(DArray *array, DItem item, DSize index);

DItem da_remove(DArray *array, DSize index);

DItem da_get(DArray *array, DSize index);

// Private methods
void *_da_malloc(DSize size);

void *_da_realloc(DItem *array, DMethod method);

void _da_free(void *mem);

DSize _da_new_capacity(DSize cap, DMethod method);

#endif /* DYNAMIC_ARRAY_H_ */
