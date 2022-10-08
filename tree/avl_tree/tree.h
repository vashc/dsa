#pragma once
#ifndef DSA_TREE_H
#define DSA_TREE_H

#include "stdlib.h"

typedef int Key;

typedef struct Node {
    Key key;
    unsigned char height;
    struct Node *left;
    struct Node *right;
} Node;

// Public methods
Node *avl_new(Key key);

void avl_free(Node *node);

Node *avl_insert(Node *node, Key key);

Node *avl_remove(Node *node, Key key);

Node *avl_search(Node *node, Key key);

unsigned char avl_height(Node *node);

void avl_print(Node *node);

// Private methods
int _avl_balance_factor(Node *node);

void _avl_adjust_height(Node *node);

Node *_avl_left_rotation(Node *node);

Node *_avl_right_rotation(Node *node);

Node *_avl_rebalance(Node *node);

Node *_avl_find_min(Node *node);

Node *_avl_remove_min(Node *node);

void _avl_print(Node *node, unsigned char level);

#endif //DSA_TREE_H
