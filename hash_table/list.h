#pragma once
#ifndef DSA_LIST_H
#define DSA_LIST_H

typedef void *LValue;

typedef struct Node {
    LValue value;
    struct Node *next;
} Node;

// Public methods
Node *l_new(LValue value);

void l_free(Node *node);

Node *l_push(Node *node, LValue value);

Node *l_pop(Node *node);

Node *l_remove(Node *node, LValue value);

Node *l_search(Node *node, LValue value);

#endif //DSA_LIST_H
