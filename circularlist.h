#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

typedef struct cnode
{
    struct cnode *perv;
    int frq;
    char *word;
    struct cnode *next;
}circle;

typedef struct snode
{
    char *word;
    struct snode *next;
}single;

circle *insert_sortedc(circle *list, int frq, char *word);
void print_listc(circle *list);
void unloadc(circle *list);
single *insert_sorted(single *list, char *word);
void print_list(single *list);
void unload(single *list);

#endif