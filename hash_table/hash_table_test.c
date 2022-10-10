#include "chained_hash_table.h"
#include "oaddressed_hash_table.h"
#include "pjw32.h"
#include "assert.h"

int main() {
    // Test chained hash table with PJW-32 hash function
    CHashTable *chash_table = cht_new(hash_pjw32);

    cht_insert(chash_table, "lol");
    assert(cht_search(chash_table, "lol") == 0);

    // Try to add already existing values
    cht_insert(chash_table, "lol");
    cht_insert(chash_table, "lol");
    assert(chash_table->size == 1);

    cht_insert(chash_table, "kek");
    assert(chash_table->size == 2);
    assert(cht_search(chash_table, "kek") == 0);

    cht_remove(chash_table, "lol");
    assert(cht_search(chash_table, "lol") == -1);

    cht_free(chash_table);

    // Open-addressed has table with PJW-32 has function and linear probing
    assert(hash_pjw32("string") * 2 == probing_linear(hash_pjw32, "string", 1));

    OAHashTable *ohash_table = oht_new(hash_pjw32, probing_linear);

    oht_insert(ohash_table, "lol");
    assert(oht_search(ohash_table, "lol") == 0);

    // Try to add already existing values
    oht_insert(ohash_table, "lol");
    oht_insert(ohash_table, "lol");
    assert(ohash_table->size == 1);

    oht_insert(ohash_table, "kek");
    assert(ohash_table->size == 2);
    assert(oht_search(ohash_table, "kek") == 0);

    oht_remove(ohash_table, "lol");
    assert(oht_search(ohash_table, "lol") == -1);

    // Assure that the element was deleted lazily
    assert(ohash_table->table[hash_pjw32("lol") % ohash_table->capacity]->is_deleted);

    oht_free(ohash_table);
}
