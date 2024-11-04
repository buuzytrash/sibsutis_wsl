#include "avltree.h"

int main()
{
    srand(time(0));
    char words[50000][30];
    FILE *file = fopen("b.txt", "r");
    FILE *data = fopen("data.txt", "a");
    double t1, t2, t3, ftime;
    int index;

    fscanf(file, "%s", words[0]);
    struct avltree *tree = avltree_create(0, words[0]);
    for (int i = 1; i < 50000; i++)
    {
        fscanf(file, "%s", words[i]);
        tree = avltree_add(tree, i, words[i]);
        if (i % 500 == 0)
        {
            index = rand() % i;
            for (int j = 0; j < 10; j++)
            {
                t1 = wtime();
                avltree_lookup(tree, index);
                t2 = wtime();
                t3 = t2 - t1;
                ftime += t3;
            }
            ftime /= 10;
            // printf("%d-ый элемент найден в дереве из %d элементов за %f с\n", index, i, ftime);
        }
    }

    // printf("%d %d\n", avltree_height(tree), avltree_balance(tree));

    fclose(file);
    avltree_free(tree);

    struct avltree *minus_tree = avltree_create(0, words[0]);
    for (int i = 1; i < 10; i++)
    {
        minus_tree = avltree_add(minus_tree, -(i), words[i]);
    }
    minus_tree = avltree_add(minus_tree, -6, "kit");
    avltree_print_dfs(minus_tree, 0);
    printf("высота - %d баланс - %d\n", avltree_height(minus_tree), avltree_balance(minus_tree));

    return 0;
}