#include "trie.h"
#include "assert.h"
#include "string.h"
#include "stdio.h"

int main() {
    Node *trie = t_new();

    t_insert(trie, "k", 1, 1);
    t_insert(trie, "kek", 3, 2);
    t_insert(trie, "kekov", 5, 3);
    t_insert(trie, "lol", 3, 4);
    t_insert(trie, "lek", 3, 5);

    int found;
    Node *res = NULL;
    found = t_search(trie, "k", 1, &res);
    assert(found == 0);
    assert(res->value == 1);
    found = t_search(trie, "kek", 3, &res);
    assert(found == 0);
    assert(res->value == 2);
    found = t_search(trie, "kekov", 5, &res);
    assert(found == 0);
    assert(res->value == 3);
    found = t_search(trie, "lol", 3, &res);
    assert(found == 0);
    assert(res->value == 4);
    found = t_search(trie, "lek", 3, &res);
    assert(found == 0);
    assert(res->value == 5);

    t_print(trie, 10);

    t_print_prefix(trie, "l", 1, 10);

    t_free(trie);
}