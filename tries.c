#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tries.h"

// Create
trie *create_node(void)
{
    trie *n = malloc(sizeof(trie));

    if (n == NULL)
    {
        return NULL;
    }

    n->is_word = false;

    for (int i = 0; i < 26; i++)
    {
        n->children[i] = NULL;
    }

    return n;
}

// Insert
trie *insert_word(trie *root, char *word)
{
    trie *current = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';

        if (current->children[index] == NULL)
        {
            current->children[index] = create_node();

            if (current->children[index] == NULL)
            {
                return NULL;
            }
        }

        current = current->children[index];
    }

    current->is_word = true;

    return root;
}


// Print
void print_from_node(trie *root, char *buffer, int depth)
{
    if (root->is_word)
    {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < 26; i++)
    {
        if (root->children[i] != NULL)
        {
            buffer[depth] = 'a' + i;
            print_from_node(root->children[i], buffer, depth + 1);
        }
    }
}

// Prints all words beginning with a prefix
void print_prefix(trie *root, char *prefix)
{
    trie *current = root;
    char buffer[100];
    int depth = 0;

    while (prefix[depth] != '\0')
    {
        int index = prefix[depth] - 'a';

        if (current->children[index] == NULL)
        {
            printf("No words found with prefix \"%s\"\n", prefix);
            return;
        }

        buffer[depth] = prefix[depth];
        current = current->children[index];
        depth++;
    }

    print_from_node(current, buffer, depth);
}

// Frees all trie nodes
void unloadr(trie *root)
{
    if (root == NULL)
    {
        printf("Empty tries\n");
        return;
    }

    for (int i = 0; i < 26; i++)
    {
        if (root->children[i] != NULL)
        {
            unloadr(root->children[i]);
        }
    }

    free(root);
}