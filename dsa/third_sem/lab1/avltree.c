#include "avltree.h"

struct avltree *avltree_create(int key, char *value) // создание авл-дерева
{
    struct avltree *node;

    node = malloc(sizeof(*node));
    if (node != NULL)
    {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }
    return node;
}

struct avltree *avltree_add(struct avltree *tree, int key, char *value) // добавление элемента
{
    if (tree == NULL)
    {
        return avltree_create(key, value);
        // printf("%d\n", tree->key);
    }
    if (key < tree->key)
    {
        // добавление в левое поддерево
        tree->left = avltree_add(tree->left, key, value);
        if (avltree_height(tree->left) - avltree_height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = avltree_right_rotate(tree);
            else
                tree = avltree_leftright_rotate(tree);
        }
        // printf("%d\n", tree->key);
    }
    else if (key >= tree->key)
    {
        // добавление в правое поддерево
        tree->right = avltree_add(tree->right, key, value);
        if (avltree_height(tree->right) - avltree_height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = avltree_left_rotate(tree);
            else
                tree = avltree_rightleft_rotate(tree);
        }
        // printf("%d\n", tree->key);
    }
    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;

    return tree;
}
struct avltree *avltree_delete(struct avltree *tree, int key) // delete элемента
{
    if (tree == NULL)
        return tree;

    if (key < tree->key)
    {
        tree->left = avltree_delete(tree->left, key);
    }
    else if (key > tree->key)
    {
        tree->right = avltree_delete(tree->right, key);
    }
    else
    {
        struct avltree *q = tree->left;
        struct avltree *p = tree->right;
        tree = NULL;
        if (p == NULL)
            return q;
        struct avltree *min = avltree_min(p);
        min->right = delete_min(p);
        min->left = q;
        return balance_delete(min);
    }
    return balance_delete(tree);
}

struct avltree *avltree_min(struct avltree *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->left != NULL)
        tree = tree->left;
    return tree;
} // поиск минимального элемента
struct avltree *avltree_max(struct avltree *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

struct avltree *avltree_lookup(struct avltree *tree, int key) // поиск узла по ключу
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

void avltree_free(struct avltree *tree) // удаление авл-дерева (обход в обратном порядке)
{
    if (tree == NULL)
        return;

    avltree_free(tree->left);
    avltree_free(tree->right);
    free(tree);
}

int avltree_height(struct avltree *tree) // высота дерева
{
    return (tree != NULL) ? tree->height : -1;
}

int avltree_balance(struct avltree *tree)
{
    return avltree_height(tree->right) - avltree_height(tree->left);
}
struct avltree *avltree_right_rotate(struct avltree *tree) // правый поворот
{
    struct avltree *left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;

    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    left->height = imax2(avltree_height(left->left), tree->height) + 1;
    return left;
}
struct avltree *avltree_left_rotate(struct avltree *tree) // правый поворот
{
    struct avltree *right;

    right = tree->right;
    tree->right = right->left;
    right->left = tree;

    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    right->height = imax2(avltree_height(right->right), tree->height) + 1;

    return right;
}
struct avltree *avltree_leftright_rotate(struct avltree *tree)
{
    tree->left = avltree_left_rotate(tree->left);
    return avltree_right_rotate(tree);
}
struct avltree *avltree_rightleft_rotate(struct avltree *tree)
{
    tree->right = avltree_right_rotate(tree->right);
    return avltree_left_rotate(tree);
}

void avltree_print_dfs(struct avltree *tree, int level)
{
    int i;

    if (tree == NULL)

        return;

    for (i = 0; i < level; i++)

        printf(" ");

    printf("%d\n", tree->key);

    avltree_print_dfs(tree->left, level + 1);
    avltree_print_dfs(tree->right, level + 1);
}

int imax2(int height_left, int height_right)
{
    if (height_left > height_right)
        return height_left;
    else
        return height_right;
}

struct avltree *balance_delete(struct avltree *tree)
{
    tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    if (avltree_balance(tree) == 2)
    {
        if (avltree_balance(tree->right) < 0)
            tree->right = avltree_right_rotate(tree->right);
        return avltree_left_rotate(tree);
    }
    if (avltree_balance(tree) == -2)
    {
        printf("%d\n", avltree_balance(tree->right));
        if (avltree_balance(tree->left) > 0)
            tree->left = avltree_right_rotate(tree->left);
        return avltree_right_rotate(tree);
    }
    return tree;
}
struct avltree *delete_min(struct avltree *tree)
{
    if (tree->left == 0)
        return tree->right;
    tree->left = delete_min(tree->left);
    return balance_delete(tree);
}
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
};
