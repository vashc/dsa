#pragma once
#ifndef DSA_CHAINED_HASH_TABLE_H
#define DSA_CHAINED_HASH_TABLE_H

#include "list.h"

#define DEFAULT_HASH_SET_CAPACITY 1 << 10

typedef void *Value;

// CHashTable represents chained hash table
typedef struct CHashTable {
    unsigned capacity; // Current maximum number of buckets
    unsigned size; // Number of buckets allocated
    Node **table; // Array of bucket references

    unsigned int (*hash)(const char *value); // Encapsulated hash function
} CHashTable;

// Public methods
CHashTable *cht_new(unsigned int (*hash)(const char *value));

void cht_free(CHashTable *hash_table);

int cht_insert(CHashTable *hash_table, Value value);

int cht_search(CHashTable *hash_table, Value value);

int cht_remove(CHashTable *hash_table, Value value);

#endif //DSA_CHAINED_HASH_TABLE_H
