#include "tree.h"
#include "assert.h"
#include "stdio.h"

int main() {
    Node *treap = tr_new(0, rand());
    assert(treap->key == 0);

    for (int i = 1; i < 10; i++)
        treap = tr_insert(treap, i);

    Node *node = tr_search(treap, 9);
    assert(node->key == 9);

    node = tr_search(treap, 10);
    assert(node == NULL);

    treap = tr_remove(treap, 4);
    node = tr_search(treap, 4);
    assert(node == NULL);
    treap = tr_remove(treap, 0);
    node = tr_search(treap, 0);
    assert(node == NULL);

    // Try to remove non-existent node
    Node *root = treap;
    treap = tr_remove(treap, 0);
    assert(root == treap);

    tr_free(treap);
}
