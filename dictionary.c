// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
int dict_size = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // creates a temp variable that stores a lower-cased version of the word
    char temp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
    {
        temp[i] = tolower(word[i]);
    }
    temp[len] = '\0';

    // find what index of the array the word should be in
    int index = hash(temp);

    // if hashtable is empty at index, return false
    if (table[index] == NULL)
    {
        return false;
    }

    // create cursor to compare to word
    node* cursor = table[index];

    // if hashtable is not empty at index, iterate through words and compare
    while (cursor != NULL)
    {
        if (strcmp(temp, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    // if you don't find the word, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char* dictionary)
{
    // TODO
    // opens dictionary
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
        return false;

    // create an array for word to be stored in
    char word[LENGTH+1];

    // scan through the file, loading each word into the hash table
    while (fscanf(file, "%s\n", word)!= EOF)
    {
        // increment dictionary size
        dict_size++;

        // allocate memory for new word
        node* newWord = malloc(sizeof(node));

        // put word in the new node
        strcpy(newWord->word, word);

        // find what index of the array the word should go in
        int index = hash(word);

        // if hashtable is empty at index, insert
        if (table[index] == NULL)
        {
            table[index] = newWord;
            newWord->next = NULL;
        }

        // if hashtable is not empty at index, append
        else
        {
            newWord->next = table[index];
            table[index] = newWord;
        }

    }

    // close file
    fclose(file);


    // return true if successful
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i=0; i<N; i++)
    {
        if(table[i] != NULL)
        {
            node *cursor = malloc(sizeof(node));

            while(table[i] != NULL)
            {
                cursor = table[i];
                table[i] = cursor->next;
                free(cursor);
            }
        }
    }

    return true;
}