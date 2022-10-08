#include "tree.h"
#include "assert.h"
#include "stdio.h"

int main() {
    Node *tree = avl_new(0);
    assert(tree->key == 0);

    for (int i = 0; i < 1 << 10; i++) {
        tree = avl_insert(tree, i);
    }
    assert(avl_height(tree) == 11);

    tree = avl_remove(tree, 0);
    Node *deleted_node = avl_search(tree, 0);
    // We still have one node with `0` key
    assert(deleted_node != NULL);

    tree = avl_remove(tree, 0);
    deleted_node = avl_search(tree, 0);
    // But now we don't have any nodes with the `0` key
    assert(deleted_node == NULL);

    avl_free(tree);

    tree = avl_new(0);
    for (int i = 0; i < 10; i++)
        tree = avl_insert(tree, i);
    avl_print(tree);

    // Remove the root node and reprint the tree
    tree = avl_remove(tree, 2);
    avl_print(tree);
    // The root node should have key equals to `3` after removing
    assert(tree->key == 3);

    avl_free(tree);
}
