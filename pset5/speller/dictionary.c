// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

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
    // Hash the word to obtain its hash value
    int index = hash(word);
    // Search the hash table at the location specified by the word’s hash value
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // Return true if the word is found
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
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
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (!source)
    {
        return false;
    }

    // Read each word in the file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        // Add each word to the hash table
        // Create space for a new hash table node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // Copy the word into the new node
        strcpy(n->word, word);
        // Hash the word to obtain its hash value
        int index = hash(word);
        // Insert the new node into the hash table (using the index specified by its hash value)
        n->next = table[index];
        table[index] = n;
    }
    // Close the dictionary file
    fclose(source);
    return true;
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
// Each time size is called, iterate through the words in the hash table to count them up. Return that count.
unsigned int size(void)
{
    // TODO
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *ptr = table[i]; ptr != NULL; ptr = ptr->next)
        {
            count++;
        }
    }
    return count;
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
