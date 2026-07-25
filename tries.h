#ifndef TRIES_H
#define TRIES_H

typedef struct tnode
{
    bool is_word;
    struct tnode *children[26];
} trie;

// Function prototypes
trie *create_node(void);
trie *insert_word(trie *root, char *word);
void print_from_node(trie *root, char *buffer, int depth);
void print_prefix(trie *root, char *prefix);
void unloadr(trie *root);

#endif

