#pragma once
#ifndef DSA_TRIE_H
#define DSA_TRIE_H

#include "stdbool.h"
#include "stdlib.h"

#define ALPHABET_SIZE 26

#define LEN(arr) (sizeof((arr)) / sizeof((arr)[0]))
#define CHAR_TO_INDEX(c) ((int)(c) - (int)'a')
#define INDEX_TO_CHAR(i) ((i) + (int)'a')

typedef int Value;

typedef struct Node {
    struct Node *children[ALPHABET_SIZE];
    bool is_terminal;
    Value value; // For associative array only
} Node;

// Public methods
Node *t_new();

void t_free(Node *trie);

int t_insert(Node *trie, const char *word, unsigned word_len, Value value);

int t_search(Node *trie, const char *word, unsigned word_len, Node **result);

void t_print(Node *trie, unsigned max_prefix_len);

void t_print_prefix(Node *trie, const char *prefix, unsigned prefix_len, unsigned max_prefix_len);

// Private methods
int _t_malloc(Node **trie);

void _t_print(Node *trie, char current_prefix[], unsigned prefix_len, unsigned level);

int _t_search(Node *trie, const char *word, unsigned word_len, Node **result);

#endif // DSA_TRIE_H
