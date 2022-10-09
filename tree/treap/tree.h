#pragma once
#ifndef DSA_TREE_H
#define DSA_TREE_H

#include "stdlib.h"

typedef int Key;
typedef int Priority;

typedef struct Node {
    Key key; // `x` coordinate
    Priority priority; // `y` coordinate
    struct Node *left;
    struct Node *right;
} Node;

// Public methods
Node *tr_new(Key key, Priority priority);

void tr_free(Node *node);

Node *tr_insert(Node *node, Key key);

Node *tr_remove(Node *node, Key key);

Node *tr_search(Node *node, Key key);

void tr_print(Node *node);

// Private methods
Node *tr_insert(Node *node, Key key);

Node *_tr_merge(Node *left, Node *right);

void _tr_split(Node *node, Key key, Node **left, Node **right);

void _tr_print(Node *node, unsigned char level);

#endif //DSA_TREE_H
