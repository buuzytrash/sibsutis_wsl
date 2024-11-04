#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __tries__
#define __tries__

struct trie
{
    char *value;
    char ch;
    struct trie *sibling; /* Sibling node */
    struct trie *child;   /* First child node */
};

struct trie *trie_create();
struct trie *trie_insert(struct trie *root, char *key, char *value);
struct trie *trie_lookup(struct trie *root, char *key);
struct trie *trie_delete(struct trie *root, char *key);
void trie_print(struct trie *root, int level, FILE *file);

#endif