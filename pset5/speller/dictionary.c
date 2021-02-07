// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

// Hash table
node *table[N];

// Size variable
int current_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get needed list
    node *head = table[hash(word)];

    while (head)
    {
        // Check if word already exists in the list
        if (!(strcasecmp(head->word, word)))
        {
            return true;
        }
        // Iterate over the list
        head = head->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return (unsigned int)toupper(word[0]) - 65;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // File ptr
    FILE *file;
    // Buffer
    char buf[LENGTH + 1];

    // Open file and check return value of a file
    if (!(file = fopen(dictionary, "r")))
    {
        return false;
    }

    // Read the file
    while (fscanf(file, "%s", buf) != EOF)
    {
        // Node ptr
        node *n;

        // Create new node
        if (!(n = malloc(sizeof(node))))
        {
            return false;
        }

        // Copy word from buf to node
        strcpy(n->word, buf);

        // Get hash value
        unsigned int h = hash(buf);

        // Add node to the list
        n->next = table[h];
        table[h] = n;

        // Track size
        current_size++;
        // bzero(buf, LENGTH);
    }

    // Close the file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return current_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over array
    for (int i = 0; i < N; i++)
    {
        // Get list head
        node *head = table[i];
        // Iterate over list
        while (head)
        {
            // Save head;
            node *tmp = head;
            // Move coursor
            head = head->next;
            // Free saved node
            free(tmp);
        }
    }
    return true;
}
