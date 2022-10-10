#include "list.h"
#include "stdlib.h"
#include "stdio.h"

Node *l_new(LValue value) {
    Node *node = malloc(sizeof(Node));
    if (NULL == node)
        abort();

    node->value = value;
    node->next = NULL;

    return node;
}

void l_free(Node *node) {
    if (NULL == node)
        return;

    l_free(node->next);

    free(node);
}

Node *l_push(Node *node, LValue value) {
    Node *new_node = l_new(value);
    new_node->next = node;

    return new_node;
}

Node *l_pop(Node *node) {
    if (NULL == node)
        return NULL;

    Node *curr_node = node->next;
    free(node);

    return curr_node;
}

Node* l_remove(Node *node, LValue value) {
    if (NULL == node)
        return NULL;

    Node *prev_node = node, *curr_node = node;

    while (curr_node) {
        if (value == curr_node->value) {
            // Remove the head of the list
            if (curr_node == node) {
                return l_pop(node);
            }

            prev_node->next = curr_node->next;
            // Don't forget to remove this node from memory
            free(curr_node);

            return 0;
        }

        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    // Specified value has not been found
    return node;
}

Node *l_search(Node *node, LValue value) {
    for (Node *curr_node = node; curr_node; curr_node = curr_node->next) {
        if (value == curr_node->value)
            return curr_node;
    }

    return NULL;
}
