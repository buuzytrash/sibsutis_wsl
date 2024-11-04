#include "bstree.h"

int main()
{
    char words[1000][30];
    int s = 0;
    char *w;
    FILE *file = fopen("b.txt", "r");

    for (int i = 0; i < 1000; i++)
    {
        fscanf(file, "%s", words[i]);
    }

    struct bstree *tree = bstree_create(words[0], 0);
    printf("\n");
    fclose(file);
    for (int i = 2; i <= 1000; i++)
    {
        bstree_add(tree, words[i - 1], i - 1);
    }

    TraversInOrder(tree);

    return 0;
}