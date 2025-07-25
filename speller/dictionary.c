// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int count_words = 0; // no repetitive actions, use this and return it from the size function

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // check if a word exists in the dictionary, first make the load function so you have ll
    // increment from table[0], iterate through every element till pointer == null, then move on to
    // the next table[1]

    // no way of taking hash_value from load(), so we calculate again
    int hash_value = hash(word);

    // create a temp which will go to table[hash_value], next we check through the whole list
    node *temp = table[hash_value];

    while (temp != NULL)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open file
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }
    // read words one by one into something (maybe to a place holder which we will then pass onto
    // the hash function)
    char holder[46];
    // reset place holder to nothing at the end of the loop
    while (fscanf(dic, "%s", holder) != EOF)
    {
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }
        strcpy(new->word, holder);
        // now the word is seperated and copied, now we need to get a hash value for it
        int hash_value = hash(new->word);
        new->next = table[hash_value];
        table[hash_value] = new;
        count_words++;
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // add simple counter (declared golbally) in the add words part of load()
    return count_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // ezpz, table (0-N), traverse every link list, free and then increment table

    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        while (temp != NULL)
        {
            node *llelement = temp->next;
            free(temp);
            temp = llelement;
        }
        table[i] = NULL;
    }

    return true;
}
