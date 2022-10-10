#include "oaddressed_hash_table.h"
#include "stdlib.h"

OAHashTable *oht_new(hash *hash_func, probing *probing_func) {
    OAHashTable *hash_table = malloc(sizeof(OAHashTable));
    if (NULL == hash_table)
        abort();

    hash_table->size = 0;
    hash_table->capacity = DEFAULT_HASH_SET_CAPACITY;
    hash_table->table = calloc(hash_table->capacity, sizeof(ONode *));
    hash_table->hash_func = hash_func;
    hash_table->probing_func = probing_func;

    return hash_table;
}

void oht_free(OAHashTable *hash_table) {
    if (NULL == hash_table)
        return;

    for (int i = 0; i < hash_table->capacity; i++)
        free(hash_table->table[i]);

    free(hash_table->table);
    free(hash_table);
}

int oht_insert(OAHashTable *hash_table, Value value) {
    // Do nothing if the data is already in the table
    if (0 == oht_search(hash_table, value))
        return 1;

    for (int i = 0; i < hash_table->capacity; i++) {
        unsigned int table_idx = hash_table->probing_func(hash_table->hash_func, value, i) % hash_table->capacity;

        if (NULL == hash_table->table[table_idx])
            hash_table->table[table_idx] = _oht_new_node(value, false);
        else if (hash_table->table[table_idx]->is_deleted) {
            hash_table->table[table_idx]->value = value;
            hash_table->table[table_idx]->is_deleted = false;
        }

        hash_table->size++;
        return 0;
    }

    return -1;
}

int oht_search(struct OAHashTable *hash_table, Value value) {
    for (int i = 0; i < hash_table->capacity; i++) {
        unsigned int table_idx = hash_table->probing_func(hash_table->hash_func, value, i) % hash_table->capacity;

        if (NULL == hash_table->table[table_idx])
            return -1;

        if (value == hash_table->table[table_idx]->value && !(hash_table->table[table_idx]->is_deleted))
            return 0;
    }

    return -1;
}

int oht_remove(OAHashTable *hash_table, Value value) {
    for (int i = 0; i < hash_table->capacity; i++) {
        unsigned int table_idx = hash_table->probing_func(hash_table->hash_func, value, i) % hash_table->capacity;

        if (NULL == hash_table->table[table_idx])
            // The value has not been found
            return -1;
        else if (hash_table->table[table_idx]->is_deleted) {
            continue;
        } else if (value == hash_table->table[table_idx]->value) {
            hash_table->table[table_idx]->is_deleted = true;
            hash_table->size--;
            return 0;
        }
    }

    return -1;
}

unsigned int probing_linear(hash *hash_func, const char *value, int probe_idx) {
    unsigned int hashed_value = hash_func(value);
    return hashed_value + probe_idx * hashed_value;
}

unsigned int probing_quadratic(hash *hash_func, const char *value, int probe_idx) {
    unsigned int hashed_value = hash_func(value);
    return hashed_value + probe_idx * probe_idx * hashed_value;
}

ONode *_oht_new_node(Value value, bool is_deleted) {
    ONode *node = malloc(sizeof(struct ONode));
    if (NULL == node)
        abort();

    node->value = value;
    node->is_deleted = is_deleted;

    return node;
}