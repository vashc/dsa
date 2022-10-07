#pragma once
#ifndef DSA_DYNAMIC_ARRAY_H
#define DSA_DYNAMIC_ARRAY_H

// Possible reallocation methods
#define METHOD_SINGLE 0
#define METHOD_FACTOR 1

#define INITIAL_CAP 4

typedef int Item;
typedef unsigned int Size;
typedef unsigned int Method;

typedef struct DArray {
    Item *array;
    Size size;
    Size cap;
} DArray;

// Public methods
DArray *da_new(Size cap);

void da_free(DArray *array);

void da_add(DArray *array, Item item);

void da_insert(DArray *array, Item item, Size index);

Item da_remove(DArray *array, Size index);

Item da_get(DArray *array, Size index);

// Private methods
void *_da_malloc(Size size);

void _da_free(void *mem);

Size _da_new_capacity(Size cap, Method method);

#endif /* DSA_DYNAMIC_ARRAY_H */
