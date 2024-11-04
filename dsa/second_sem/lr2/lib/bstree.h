#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#ifndef __bstree__
#define __bstree__

struct bstree
{
    char *key;
    uint32_t value;

    struct bstree *left;
    struct bstree *right;
};
struct bstree *bstree_create(char *key, uint32_t value);
void bstree_add(struct bstree *tree, char *key, uint32_t value);
struct bstree *bstree_lookup(struct bstree *tree, char *key);
// struct bstree *bstree_delete(struct bstree *tree, char *key);
struct bstree *bstree_min(struct bstree *tree);
struct bstree *bstree_max(struct bstree *tree);
void TraversInOrder(struct bstree *tree);
double wtime();

#endif