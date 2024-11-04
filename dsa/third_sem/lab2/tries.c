#include "tries.h"

struct trie *trie_create()
{
    struct trie *node;
    if ((node = malloc(sizeof(*node))) == NULL)
        return NULL;
    node->ch = '\0';
    node->value = NULL;
    node->sibling = NULL;
    node->child = NULL;
    return node;
}

struct trie *trie_lookup(struct trie *root, char *key)
{
    struct trie *node, *list;
    for (list = root; *key != '\0'; key++)
    {
        for (node = list; node != NULL; node = node->sibling)
        {
            if (node->ch == *key)
                break;
        }
        if (node != NULL)
            list = node->child;
        else
            return NULL;
    }
    return node->value; /* Node must be a leaf */
}

struct trie *trie_insert(struct trie *root, char *key, char *value)
{
    struct trie *node, *parent, *list;
    parent = NULL;
    list = root;
    for (; *key != '\0'; key++)
    {
        /* Lookup sibling node */
        for (node = list; node != NULL; node = node->sibling)
        {
            if (node->ch == *key)
                break;
        }
        if (node == NULL)
        { /* Node not found. Add new node */
            node = trie_create();
            node->ch = *key;
            node->sibling = list;
            if (parent != NULL)
                parent->child = node;
            else
                root = node;
            list = NULL;
        }
        else
        { /* Node found. Move to next level */
            list = node->child;
        }
        parent = node;
    }
    /* Update value in leaf */
    if (node->value != NULL)
        free(node->value);
    node->value = strdup(value);
    return root;
}

struct trie *trie_delete_dfs(struct trie *root, struct trie *parent,
                             char *key, int *found)
{
    struct trie *node, *prev = NULL;
    *found = (*key == '\0' && root == NULL) ? 1 : 0;
    if (root == NULL || *key == '\0')
        return root;
    for (node = root; node != NULL; node = node->sibling)
    {
        if (node->ch == *key)
            break;
        prev = node;
    }
    if (node == NULL)
        return root;
    trie_delete_dfs(node->child, node, key + 1, found);
    if (*found > 0 && node->child == NULL)
    {
        /* Delete node */
        if (prev != NULL)
            prev->sibling = node->sibling;
        else
        {
            if (parent != NULL)
                parent->child = node->sibling;
            else
                root = node->sibling;
        }
        free(node->value);
        free(node);
    }
    return root;
}
struct trie *trie_delete(struct trie *root, char *key)
{
    int found;
    return trie_delete_dfs(root, NULL, key, &found);
}

void trie_print(struct trie *root, int level, FILE *file)
{
    int i;

    if (root == NULL)

        return;

    for (i = 0; i < level; i++)
    {
        printf(" ");
        fprintf(file, " ");
    }

    printf("%c\t\t", root->ch);
    fprintf(file, "%c\t\t", root->ch);
    if (root->value != 0)
    {
        printf("%s\t", root->value);
        fprintf(file, "%s\t", root->value);
    }
    printf("%d\n", level);
    fprintf(file, "%d\n", level);

    trie_print(root->child, level + 1, file);
    trie_print(root->sibling, level, file);
}