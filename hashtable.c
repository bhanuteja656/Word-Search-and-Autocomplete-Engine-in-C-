#include "hashtable.h"
#include "stdmine.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX_COUNT 26

unsigned int count = 0;


hashnode *inserthash(hashnode *table[], char *name)
{
    hashnode *n = malloc(sizeof(hashnode));

    if (n == NULL)
    {
        return NULL;
    }

    n->name = malloc(strlen(name) + 1);

    if (n->name == NULL)
    {
        free(n);
        return NULL;
    }

    strcpy(n->name, name);
    n->freq = 0;
    n->link = NULL;

    int index = hash(name);
    hashnode *ptr = table[index];
    while (ptr != NULL)
    {
        if (strcmp(ptr->name, name) == 0)
        {
            ptr->freq = ptr->freq + 1;
            free(n->name);
            free(n);
            return table[index];
        }
        ptr = ptr->link;
    }
    if (table[index] == NULL)
    {
        table[index] = n;
        count = count + 1;
    }
    else if (score(n->name) < score(table[index]->name))
    {
        n->link = table[index];
        table[index] = n;
        count = count + 1;
    }
    else
    {
        hashnode *ptr = table[index];

        while (ptr != NULL)
        {
            if (ptr->link == NULL)
            {
                ptr->link = n;
                count = count + 1;
                break;
            }

            if (score(n->name) < score(ptr->link->name))
            {
                n->link = ptr->link;
                ptr->link = n;
                count = count + 1;
                break;
            }
            ptr = ptr->link;
        }
    }
    return table[index];
}

hashnode *searchhash(hashnode *table[], char *name)
{
    int index = hash(name);

    hashnode *ptr = table[index];

    while (ptr != NULL)
    {
        if (strcmp(ptr->name, name) == 0)
        {
            ptr->freq = ptr->freq + 1;
            return ptr;
        }

        ptr = ptr->link;
    }

    return NULL;
}

void print_table_hash(hashnode *table[])
{
    if (table == NULL)
    {
        printf("Nothing here\n");
        return;
    }
    for (int i = 0; i < MAX_COUNT; i++)
    {
        printf("Bucket %2d : ", i);

        hashnode *ptr = table[i];

        while (ptr != NULL)
        {
            printf("%s %d-> ", ptr->name, ptr->freq);
            ptr = ptr->link;
        }

        printf("NULL\n");
    }
}

void unloadhash(hashnode *table[])
{
    if (table == NULL)
    {
        return;
    }
    for (int i = 0; i < MAX_COUNT; i++)
    {
        hashnode *ptr = table[i];

        while (ptr != NULL)
        {
            hashnode *next = ptr->link;
            free(ptr->name);
            free(ptr);
            ptr = next;
        }
    }
}

unsigned int hash(char *name)
{
    return toupper(name[0]) - 'A';
}

unsigned long long score(char *word)
{
    unsigned long long value = 0;

    while (*word)
    {
        char c = toupper((unsigned char)*word);

        if (c >= 'A' && c <= 'Z')
        {
            value = value * 27 + (c - 'A' + 1);
        }

        word++;
    }

    return value;
}

unsigned int size(void)
{
    return count;
}
