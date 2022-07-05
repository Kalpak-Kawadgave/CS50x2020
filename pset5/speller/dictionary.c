// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

unsigned int count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //get the hash index for search
    int index = hash(word);

    //create a transverse pointer
    node *trav = table[index];

    //loop to search the linked list
    while (trav != NULL)
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
        else
        {
            trav = trav->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == false)
    {
        return false;
    }

    //read stores the current word being read
    char *read = malloc(46 * sizeof(char));

    //read each word from the dictionary
    int c = 1;
    int index = -1;
    while (c != EOF)
    {
        //scan one word
        c = fscanf(file, "%s", read);
        if (c == EOF)
        {
            break;
        }
        count++;

        //create a new node
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            free(read);
            return false;
        }

        //copy string to new node
        strcpy(new->word, read);

        //get the index from hash
        index = hash(read);

        //add the new node to hash table
        new->next = table[index];
        table[index] = new;
    }
    free(read);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N + 1; i++)
    {
        node *trav = table[i];
        while (trav != NULL)
        {
            trav = trav->next;
            free(table[i]);
            table[i] = trav;
        }
    }
    return true;
}