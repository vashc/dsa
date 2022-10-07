#include "trie.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

Node *t_new() {
    Node *trie = NULL;
    int ret = _t_malloc(&trie);
    if (-1 == ret)
        abort();

    return trie;
}

void t_free(Node *trie) {
    for (int i = 0; i < LEN(trie->children); i++) {
        if (NULL != trie->children[i])
            t_free(trie->children[i]);
    }

    free(trie);
}

// When trie is used as associative array, it will substitute the previous value
// with the same key
int t_insert(Node *trie, const char *word, unsigned word_len, Value value) {
    int ret = 0;

    Node *current_node = trie;
    size_t child_index;

    for (int level = 0; level < word_len; level++) {
        child_index = CHAR_TO_INDEX(word[level]);

        // Check out-of-bounds errors
        if (ALPHABET_SIZE <= child_index)
            return -1;

        // Allocate a new node if necessary
        if (NULL == current_node->children[child_index]) {
            ret = _t_malloc(&current_node->children[child_index]);
            if (-1 == ret)
                return ret;
        }

        current_node = current_node->children[child_index];
    }

    // Mark last node as a terminal one
    current_node->is_terminal = true;
    current_node->value = value;

    return ret;
}

int t_search(Node *trie, const char *word, unsigned word_len, Node **result) {
    int prefix_found = _t_search(trie, word, word_len, result);
    if (-1 == prefix_found)
        return prefix_found;

    if ((*result)->is_terminal)
        return 0;
}

// t_print is a recursive version of the print method
void t_print(Node *trie, unsigned max_prefix_len) {
    char current_prefix[max_prefix_len];

    return _t_print(trie, current_prefix, 0, 0);
}

void t_print_prefix(Node *trie, const char *prefix, unsigned prefix_len, unsigned max_prefix_len) {
    Node *start_node = NULL;
    int prefix_found = t_search(trie, prefix, prefix_len, &start_node);
    if (-1 == prefix_found)
        return;

    char start_prefix[max_prefix_len];
    memset(start_prefix, 0, max_prefix_len);
    for (int i = 0; i < prefix_len; i++)
        start_prefix[i] = prefix[i];

    return _t_print(start_node, start_prefix, prefix_len, 0);
}

int _t_malloc(Node **trie) {
    *trie = calloc(1, sizeof(Node));
    if (NULL == *trie)
        // Memory allocation failed
        return -1;

    return 0;
}

void _t_print(Node *trie, char current_prefix[], unsigned prefix_len, unsigned level) {
    unsigned current_level = prefix_len + level;

    if (trie->is_terminal) {
        current_prefix[current_level] = '\0';
        printf("%s\n", current_prefix);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (NULL != trie->children[i]) {
            current_prefix[current_level] = INDEX_TO_CHAR(i);
            _t_print(trie->children[i], current_prefix, prefix_len, level + 1);
        }
    }
}

// _t_search is a recursive version of the search method
int _t_search(Node *trie, const char *word, unsigned word_len, Node **result) {
    if (0 == word_len) {
        *result = trie;
        return 0;
    }

    const unsigned int child_index = word[0] - 'a';

    // Specified word has not been found
    if (ALPHABET_SIZE <= child_index || NULL == trie->children[child_index])
        return -1;

    return _t_search(trie->children[child_index], word + 1, word_len - 1, result);
}
