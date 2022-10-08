#include "tree.h"
#include "stdio.h"

Node *avl_new(Key key) {
    Node *node = malloc(sizeof(Node));
    if (NULL == node)
        abort();

    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void avl_free(Node *node) {
    if (NULL == node)
        return;

    avl_free(node->left);
    avl_free(node->right);

    free(node);
}

Node *avl_insert(Node *node, Key key) {
    if (NULL == node)
        return avl_new(key);

    if (key < node->key)
        node->left = avl_insert(node->left, key);
    else
        node->right = avl_insert(node->right, key);

    return _avl_rebalance(node);
}

Node *avl_remove(Node *node, Key key) {
    if (NULL == node)
        return NULL;

    if (key < node->key)
        node->left = avl_remove(node->left, key);
    else if (key > node->key)
        node->right = avl_remove(node->right, key);
    else {
        // key == node->key
        // Memorize left and right subtree
        Node *l_child = node->left;
        Node *r_child = node->right;
        free(node);

        // Right subtree is empty, just return the left one
        if (NULL == r_child)
            return l_child;

        // Right subtree is not empty, insert node with the minimum key
        // into the root
        Node *min_node = _avl_find_min(r_child);
        min_node->right = _avl_remove_min(r_child);
        min_node->left = l_child;

        return _avl_rebalance(min_node);
    }

    return _avl_rebalance(node);
}

// avl_search is a recursive version of the search method
Node *avl_search(Node *node, Key key) {
    if (NULL == node)
        return NULL;

    if (key == node->key)
        return node;
    else if (key < node->key)
        return avl_search(node->left, key);
    else if (key > node->key)
        return avl_search(node->right, key);
    else
        return NULL;
}

// avl_height is a wrapper that works with empty nodes
unsigned char avl_height(Node *node) {
    if (NULL == node)
        return 0;

    return node->height;
}

void avl_print(Node *node) {
    return _avl_print(node, 1);
}

// _avl_balance_factor calculates balance factor for a particular node
// and works with non-empty nodes only
int _avl_balance_factor(Node *node) {
    return avl_height(node->right) - avl_height(node->left);
}

// _avl_adjust_height adjusts the height for a node
// according to the values in the left/right children
void _avl_adjust_height(Node *node) {
    unsigned char l_height = avl_height(node->left);
    unsigned char r_height = avl_height(node->right);

    node->height = (l_height > r_height ? l_height : r_height) + 1;
}

/*
 *          node                                 r_child
 *         /    \                               /       \
 *   l_subtree  r_child         =>            node     rr_subtree
 *             /       \                     /    \
 *       rl_subtree  rr_subtree       l_subtree  rl_subtree
 */
Node *_avl_left_rotation(Node *node) {
    Node *r_child = node->right;
    if (NULL == r_child)
        return node;

    node->right = r_child->left;
    r_child->left = node;
    _avl_adjust_height(node);
    _avl_adjust_height(r_child);

    return r_child;
}

/*
 *             node                        l_child
 *            /    \                       /      \
 *        l_child  r_subtree    =>   ll_subtree   node
 *         /    \                                /    \
 *  ll_subtree  lr_subtree                lr_subtree  r_subtree
 */
Node *_avl_right_rotation(Node *node) {
    Node *l_child = node->left;
    if (NULL == l_child)
        return node;

    node->left = l_child->right;
    l_child->right = node;
    _avl_adjust_height(node);
    _avl_adjust_height(l_child);

    return l_child;
}

/* _avl_rebalance is used to balance tree if the difference between left and right
 * subtrees heights more than 1, i.e. h(r_subtree) - h(l_subtree) = 2.
 *
 * If h(rl_subtree) <= h(rr_subtree), we can perform a single turn:
 *
 *          node                                 r_child
 *         /    \                               /       \
 *   l_subtree  r_child         =>            node     rr_subtree
 *             /       \      (left)         /    \
 *       rl_subtree  rr_subtree       l_subtree  rl_subtree
 *
 * If h(rl_child) > h(rr_subtree), we can perform a complex turn:
 *
 *          node                             node                                     rl_child
 *         /    \                           /    \                                   /        \
 *   l_subtree  r_child         =>    l_subtree  rl_child            =>           node        r_child
 *             /       \     (right)             /       \         (left)        /    \        /     \
 *       rl_child  rr_subtree            rll_subtree  r_child            _subtree rll_subtree rlr_subtree rr_subtree
 *      /        \                                   /       \
 * rll_subtree rlr_subtree                    rlr_subtree  rr_subtree
 *
*/
Node *_avl_rebalance(Node *node) {
    if (NULL == node)
        return NULL;

    _avl_adjust_height(node);

    if (2 == _avl_balance_factor(node)) {
        if (_avl_balance_factor(node->right) < 0)
            // That's the second case, we need a complex turn, right and left rotations
            node->right = _avl_right_rotation(node->right);
        return _avl_left_rotation(node);
    }

    if (-2 == _avl_balance_factor(node)) {
        if (_avl_balance_factor(node->left) > 0)
            // That's the inverted second case, we need a complex turn, left and right rotations
            node->left = _avl_left_rotation(node->left);
        return _avl_right_rotation(node);
    }

    // There is no need in rebalancing
    return node;
}

// _avl_find_min finds node with the minimum key in a tree
Node *_avl_find_min(Node *node) {
    return node->left ? _avl_find_min(node->left) : node;
}

// _avl_remove_min removes a node with the minimum key
Node *_avl_remove_min(Node *node) {
    if (NULL == node->left)
        return node->right;

    node->left = _avl_remove_min(node->left);

    return _avl_rebalance(node);
}

void _avl_print(Node *node, unsigned char level) {
    if (NULL != node) {
        _avl_print(node->right, level + 1);
        printf("\n\n");

        for (unsigned char i = 0; i < level; i++)
            printf("\t");

        printf("[%d]", node->key);

        _avl_print(node->left, level + 1);
    }
}
