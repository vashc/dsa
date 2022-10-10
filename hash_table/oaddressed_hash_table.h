#pragma once
#ifndef DSA_OADDRESSED_HASH_TABLE_H
#define DSA_OADDRESSED_HASH_TABLE_H

#include "stdbool.h"

#define DEFAULT_HASH_SET_CAPACITY 1 << 10

typedef unsigned int hash(const char *value);

typedef unsigned int probing(hash *hash_func, const char *value, int probe_idx);

typedef void *Value;

typedef struct ONode {
    Value value;
    bool is_deleted; // Field for lazy deletion
} ONode;

// CHashTable represents chained hash table
typedef struct OAHashTable {
    unsigned capacity; // Current maximum number of elements
    unsigned size; // Number of elements inserted
    ONode **table; // Array of elements

    hash *hash_func; // Encapsulated hash function
    probing *probing_func; // Encapsulated probing function
} OAHashTable;

// Probing methods
unsigned int probing_linear(hash *hash_func, const char *value, int probe_idx);

unsigned int probing_quadratic(hash *hash_func, const char *value, int probe_idx);

// Public methods
OAHashTable *oht_new(hash *hash_func, probing *probing_func);

void oht_free(OAHashTable *hash_table);

int oht_insert(OAHashTable *hash_table, Value value);

int oht_search(struct OAHashTable *hash_table, Value value);

int oht_remove(struct OAHashTable *hash_table, Value value);

// Private methods
ONode *_oht_new_node(Value value, bool is_deleted);

#endif //DSA_OADDRESSED_HASH_TABLE_H
