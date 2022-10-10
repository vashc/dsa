#include "chained_hash_table.h"
#include "stdlib.h"
#include "stdio.h"

CHashTable *cht_new(unsigned int (*hash)(const char *value)) {
    CHashTable *hash_table = malloc(sizeof(CHashTable));
    if (NULL == hash_table)
        abort();

    hash_table->size = 0;
    hash_table->capacity = DEFAULT_HASH_SET_CAPACITY;
    hash_table->table = calloc(hash_table->capacity, sizeof(Node *));
    hash_table->hash = hash;

    return hash_table;
}

void cht_free(CHashTable *hash_table) {
    if (NULL == hash_table)
        return;

    for (int i = 0; i < hash_table->capacity; i++) {
        l_free(hash_table->table[i]);
    }

    free(hash_table->table);
    free(hash_table);
}

int cht_insert(CHashTable *hash_table, Value value) {
    // Do nothing if the data is already in the table
    if (0 == cht_search(hash_table, value))
        return 1;

    unsigned int bucket_idx = hash_table->hash(value) % hash_table->capacity;

    if (NULL == hash_table->table[bucket_idx])
        hash_table->table[bucket_idx] = l_new(value);
    else
        hash_table->table[bucket_idx] = l_push(hash_table->table[bucket_idx], value);

    hash_table->size++;

    return 1;
}

int cht_search(CHashTable *hash_table, Value value) {
    unsigned int bucket_idx = hash_table->hash(value) % hash_table->capacity;
    Node *bucket = hash_table->table[bucket_idx];

    // Try to find value in a linked list
    if (NULL != l_search(bucket, value))
        return 0;

    return -1;
}

int cht_remove(CHashTable *hash_table, Value value) {
    // The value has not been found
    if (-1 == cht_search(hash_table, value))
        return -1;

    unsigned int bucket_idx = hash_table->hash(value) % hash_table->capacity;
    hash_table->table[bucket_idx] = l_remove(hash_table->table[bucket_idx], value);

    hash_table->size--;

    return 0;
}