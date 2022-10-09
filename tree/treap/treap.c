#include "tree.h"
#include "stdio.h"

Node *tr_new(Key key, Priority priority) {
    Node *node = malloc(sizeof(Node));
    if (NULL == node)
        abort();

    node->key = key;
    node->priority = priority;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void tr_free(Node *node) {
    if (NULL == node)
        return;

    tr_free(node->left);
    tr_free(node->right);

    free(node);
}

/*
 * tr_insert is implemented as follows:
 * - split node using `key` (left + right)
 * - create a new node with the `key` and randomly generated priority
 * - merge ((left + new node) + right)
 */
Node *tr_insert(Node *node, Key key) {
    Node *insertable_node = tr_new(key, rand());

    if (NULL == node)
        return insertable_node;

    Node *left = NULL, *right = NULL;
    _tr_split(node, key, &left, &right);

    return _tr_merge(_tr_merge(left, insertable_node), right);
}

/*
 * tr_remove is implemented as follows:
 * - split the tree using `key - 1`, so the expected node is in the right tree
 * - split the right tree using `key`, so the expected node is the root of the l_right tree (middle tree)
 * - merge left and r_right trees (without expected node)
 */
Node *tr_remove(Node *node, Key key) {
    if (NULL == node)
        return NULL;

    Node *left = NULL, *middle = NULL, *right = NULL;
    _tr_split(node, key - 1, &left, &right);
    _tr_split(right, key, &middle, &right);

    // Don't forget to free middle part
    tr_free(middle);

    return _tr_merge(left, right);
}

// tr_search is a recursive version of the search method
Node *tr_search(Node *node, Key key) {
    if (NULL == node)
        return NULL;

    if (key == node->key)
        return node;
    else if (key < node->key)
        return tr_search(node->left, key);
    else if (key > node->key)
        return tr_search(node->right, key);
    else
        return NULL;
}

void tr_print(Node *node) {
    return _tr_print(node, 0);
}

/*
 * _tr_merge is a recursive version of merge method.
 * All keys in the left tree are less than keys in the right one.
 * Let priority in the root node of the left tree is bigger than
 * priority in the root node of the right tree:
 *
 *      left + right     =>     left_root
 *        (merge)              /         \
 *                        l_subtree    [ r_subtree  +  right ]
 *                                               (merge)
 *
 */
Node *_tr_merge(Node *left, Node *right) {
    if (NULL == left)
        return right;
    if (NULL == right)
        return left;

    if (left->priority > right->priority) {
        left->right = _tr_merge(left->right, right);
        return left;
    } else {
        right->left = _tr_merge(right->left, left);
        return right;
    }
}

/*
 * _tr_split performs recursive split in such a way that
 * left tree has keys that are less than `key` and
 * right tree has keys that are bigger than `key`.
 * Let node root key is less than `key`:
 *
 *      node        =>          node_root                       =>      node_root           +      r_subtree_right
 *               (split)       /         \                             /         \
 *                            /          r_subtree                l_subtree  r_subtree_left
 *                           /            (split)
 *                          /            /       \
 *                     l_subtree r_subtree_left  r_subtree_right
 *                                (keys < key) (keys > key)
 *                    |         left          |   right    |
 */
void _tr_split(Node *node, Key key, Node **left, Node **right) {
    if (NULL == node) {
        left = NULL;
        right = NULL;
        return;
    }

    Node *new_subtree = NULL;

    if (node->key <= key) {
        if (NULL == node->right)
            right = NULL;
        else
            _tr_split(node->right, key, &new_subtree, right);

        *left = node;
        (*left)->left = node->left;
        (*left)->right = new_subtree;
    } else {
        if (NULL == node->left)
            left = NULL;
        else
            _tr_split(node->left, key, left, &new_subtree);

        *right = node;
        (*right)->left = new_subtree;
        (*right)->right = node->right;
    }
}

void _tr_print(Node *node, unsigned char level) {
    if (NULL != node) {
        _tr_print(node->right, level + 1);
        printf("\n\n");

        for (unsigned char i = 0; i < level; i++)
            printf("\t");

        printf("[%d; %f]", node->key, (float) node->priority / RAND_MAX);

        _tr_print(node->left, level + 1);
    }
}
