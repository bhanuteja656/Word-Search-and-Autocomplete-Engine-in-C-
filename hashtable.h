#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct node
{
    char *name;
    int freq;
    struct node *link;
} hashnode;


unsigned long long score(char *word);
unsigned int hash(char *name);
hashnode *inserthash(hashnode *table[], char *name);
hashnode *searchhash(hashnode *table[], char *name);
void print_table_hash(hashnode *table[]);
void unloadhash(hashnode *table[]);
unsigned int size(void);

#endif

