#include "list.h"
#include "assert.h"
#include "string.h"

int main() {
    Node *list = l_new("lol");

    list = l_push(list, "kek");
    assert(strcmp(list->value, "kek") == 0);
    assert(strcmp(list->next->value, "lol") == 0);

    list = l_remove(list, "kek");
    assert(strcmp(list->value, "lol") == 0);

    list = l_push(list, "such a word");
    list = l_pop(list);
    assert(strcmp(list->value, "lol") == 0);

    list = l_push(list, "nice");
    list = l_push(list, "word");
    Node *node = l_search(list, "word");
    assert(strcmp(node->value, "word") == 0);

    l_free(list);
}
