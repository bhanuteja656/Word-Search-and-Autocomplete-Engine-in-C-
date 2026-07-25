#include "stdmine.h"
#include "hashtable.h"
#include "circularlist.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "tries.h"
#include <unistd.h>

void database(str filename, int i, hashnode *table[], trie *root);
clock_t start, end;
double time_taken;

int main(int argc, char *argv[])
{
    /*
    * Output logging via tee + dup2.
    * This technique (redirecting stdout through popen/tee so console
    * output is duplicated to a file) is not my own idea — found it
    * while researching how to log terminal output from within a C
    * program. Implementation adapted for this project.
    */
    FILE *logpipe = popen("tee -a session_log.txt", "w");
    dup2(fileno(logpipe), STDOUT_FILENO);
    setvbuf(stdout, NULL, _IOLBF, 0);   // ← add this line



    hashnode *table[26] = {NULL};
    hashnode *targets[26] = {NULL};
    circle *repeated = NULL;
    single *history = NULL;
    trie *root = create_node(); 

    if(argc > 2)
    {
        for(int i = 1; i < argc; i++)
        {
            char *filename = malloc(strlen(argv[i]) + 1);
            strcpy(filename, argv[i]);
            database(filename, i, table, root);
            free(filename);
        }
    }
    else
    {
        char *filename = malloc(strlen(argv[1]) + 1);
        strcpy(filename, argv[1]);
        database(filename, 1, table, root);
        free(filename);
    }
    
    int i;
    do
    {
        printf("1.search\n");
        printf("2.Enter new file\n");
        printf("3.History\n");
        printf("4.all strings\n");
        printf("5.Auto compelete\n");
        printf("6.exit\n");
        i = get_int("enter the option : ");
        if(i == 1)
        {
            str target;
            do
            {
                target = get_str("Enter name to search : ");
                if (strcmp(target,"done") == 0)
                {
                    free(target);
                    break;
                }
                else
                {
                    int indexs = hash(target);
                    history = insert_sorted(history, target);
                    targets[indexs] = inserthash(targets, target);
                    start = clock();
                    hashnode *foundyes = searchhash(table, target);
                    if (foundyes != NULL)
                    {
                        printf("%s found.\n", foundyes->name);
                    }
                    else
                    {
                        printf("%s not found.\n", target);
                    }
                    end = clock();
                    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

                    printf("Time taken to search a element in hast table is %f seconds\n", time_taken);
                }
            } while(true);
        }
        else if(i == 2)
        {
            str newfile;
            newfile = get_str("Enter new file name : ");
            database(newfile, 1, table, root);
            free(newfile);
        }
        else if(i == 3)
        {
            do
            {
            printf("1. Search history\n");
            printf("2. most frquent search\n");
            printf("3.exit");
            int x = get_int("Enter the option : ");
            if(x == 1)
            {
                printf("Recent searches are in bottom old->new searchs\n");
                print_list(history);
            }
            else if(x == 2)
            {
                for (int i = 0; i < 26; i++)
                    {
                        hashnode *ptr = targets[i];
                        while (ptr != NULL)
                        {
                            repeated = insert_sortedc(repeated, ptr->freq + 1, ptr->name);
                            ptr = ptr->link;
                        }
                    }
                print_listc(repeated);
                unloadc(repeated);
                repeated = NULL;
            }
            else
            {
                break;
            }
            }while(true);
        }
        else if(i == 4)
        {
            printf("---passed search---\n");
            print_table_hash(table);
        }
        else if(i == 5)
        {
            str goat;
            goat = get_str("Enter the prefix : ");
            print_prefix(root, goat);
            free(goat);
        }
        else
        {
            unloadhash(table);
            unload(history);
            unloadc(repeated);
            unloadr(root);
            return 1;
        }
    }while(true);
    return 0;
}

void database(str filename, int i, hashnode *table[], trie *root)
{
    FILE *s = fopen(filename, "r");
    if (s == NULL)
    {
        printf("File Opening failed!\n");
        return;
    }
    char words[100];
    start = clock();
    while (fscanf(s, "%s", words) != EOF)
    {
        char *word;
        word = malloc(strlen(words) + 1);
        strcpy(word, words);

        int index = hash(word);

        table[index] = inserthash(table, word);

        root = insert_word(root, word);
        free(word);
        if (table[index] == NULL)
        {
            printf("Memory allocation failed :(\n");
            return;  
        }
    }
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time take to insert the file in both and hashtable and tries is %f seconds\n", time_taken);
    unsigned int si = size();
    printf("Number of words %u\n", si);
    fclose(s);
    return;
}
