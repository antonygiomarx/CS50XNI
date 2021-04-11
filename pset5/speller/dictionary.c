// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

trie *first = NULL;

int words_counter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int i = 0;

    trie *pointer = first;

    while (word[i] != '\0')
    {
        int k = 0;

        if (word[i] == 39)
        {
            k = 26;
        }
        else
        {
            k = tolower(word[i]) - 'a';
        }

        if (pointer -> paths[k] == NULL)
        {
            return false;
        }

        pointer = pointer -> paths[k];

        if (word[i + 1] == '\0' && pointer -> isword == true)
        {
            return true;
        }
        i++;

    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("Could not open %s. \n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

    first = calloc(1, sizeof(trie));

    if (first == NULL)
    {
        return false;
    }


    while (fscanf(file, "%s", word) == 1)
    {
        int i = 0;

        trie *pointer = first;

        while (word[i] != '\0')
        {
            int k = 0;

            if (word[i] == 39)
            {
                k = 26;
            }
            else
            {
                k = word[i] - 'a';
            }

            if (pointer -> paths[k] == NULL)
            {
                pointer -> paths[k] = calloc(1, sizeof(trie));
            }

            if (word[i + 1] == '\0')
            {
                pointer -> paths[k] -> isword = true;
            }

            pointer = pointer -> paths[k];

            i++;
        }

        words_counter++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    unload_recursive(first);

    return true;
}

void unload_recursive(trie *pointer)
{
    int i = 0;

    while (i < MPATH)
    {
        if (pointer -> paths[i] != NULL)
        {
            unload_recursive(pointer -> paths[i]);
        }
        i++;
    }

    free(pointer);

}