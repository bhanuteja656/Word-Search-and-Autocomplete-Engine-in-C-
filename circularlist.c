#include "circularlist.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// insert
single *insert_sorted(single *list, char *word)
{
    single *n = malloc(sizeof(single));
    if(n == NULL)
    {
        printf("Memory not allocated :(");
        return NULL;
    }

    n->word = word;
    n->next = NULL;

    n->next = list;
    list = n;

    return list;

}
// print
void print_list(single *list)
{
    if (list == NULL)
    {
        printf("Empty list\n");
        return;
    }
    for(single *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%s\n", ptr->word);
    }
}

//unload
void unload(single *list)
{
    if (list == NULL)
    {
        return;
    }
    while (list != NULL)
    {
        single *next = list->next;
        free(list);
        list = next;
    }
    return;
}

circle *insert_sortedc(circle *list, int frq, char *word)
{
    circle *n = malloc(sizeof(circle));
    if(n == NULL)
    {
        printf("Memory is not allocated :(\n");
        return NULL;
    }

    n->perv = NULL;
    n->word = word;
    n->frq = frq;
    n->next = NULL;

    //first element
    if(list == NULL)
    {
        n->perv = n;
        n->next = n;
        list = n;
    }

    //insert in the middle
    else if(n->frq < list->frq)
    {
        circle *last = list;
        while(last->next != list)
        {
            last = last->next;
        }
        n->perv = last;
        n->next = list;
        list->perv = n;
        last->next = n;
        list = n;
    }
    
    else 
    {
        circle *ptr = list;

        while (true)
        {
            // Insert at the end
            if (ptr->next == list)
            {
                n -> perv = ptr;
                n->next = list;
                ptr->next = n;
                list -> perv = n;
                break;
            }

            // Insert in the middle
            else if (n->frq < ptr->next->frq)
            {
                n -> perv = ptr;
                n -> next = ptr->next;
                ptr -> next -> perv = n;
                ptr -> next = n;
                break;
            }

            ptr = ptr-> next;
        }
    }
    return list;

}

//print
void print_listc(circle *list)
{
    if (list == NULL)
    {
        printf("Empty list\n");
        return;
    }
    //while(true){
    circle *ptr = list;
    printf("--- lowest ---> ");
    do
    {
        printf("%s --->", ptr -> word);
        ptr = ptr -> next;
    }
    while (ptr != list);
    printf("is the highest\n");
    
}

//unload
void unloadc(circle *list)
{
    if (list == NULL)
    {
        return;
    }

    circle *ptr = list->next;
    while (ptr != list)
    {
        circle *next = ptr-> next;
        free(ptr);
        ptr = next;
    }
    free(list);
}
