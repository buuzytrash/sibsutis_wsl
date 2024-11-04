#include "bstree.h"

struct bstree *bstree_create(char *key, uint32_t value)
{
    struct bstree *node;

    node = malloc(sizeof(*node));
    if (node != NULL)
    {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}
void bstree_add(struct bstree *tree, char *key, uint32_t value)
{
    if (tree == NULL)
        return;
    struct bstree *parent = NULL;
    while (tree != NULL)
    {
        parent = tree;
        if (key < tree->key)
            tree = tree->left;
        else if (key > tree->key)
            tree = tree->right;
        else
            return;
    }
    struct bstree *node = bstree_create(key, value);
    if (key < parent->key)
        parent->left = node;
    else
        parent->right = node;
}
struct bstree *bstree_lookup(struct bstree *tree, char *key)
{
    while (tree != NULL)
    {
        if (key == tree->key)
            return tree;
        else if (key < tree->key)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}
struct bstree *bstree_delete(struct bstree *tree, char *key)
{
    int left;

    struct bstree *parent_tree = malloc(sizeof(struct bstree));
    while (tree != NULL)
    {
        left = 0;
        if (strcmp(key, tree->key) == 0)
        {
            // printf("key : %s    tree->key : %s\n", key, tree->key);
            break;
        }
        parent_tree = tree;

        if (strcmp(key, tree->key) == 0)
        {
            break;
        }
        if (strcmp(key, tree->key) < 0)
        {
            tree = tree->left;
            left = 1;
        }
        if (strcmp(key, tree->key) > 0)
        {
            tree = tree->right;
        }
    }
}
struct bstree *bstree_min(struct bstree *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}
struct bstree *bstree_max(struct bstree *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

void TraversInOrder(struct bstree *tree)
{
    if (tree != NULL)
    {
        TraversInOrder(tree->right);
        printf("%s %d\n ", tree->key, tree->value);
        TraversInOrder(tree->left);
    }
    else
        return;
}
