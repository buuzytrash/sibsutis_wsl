#include "bstree.h"
#include "hashtab.h"

int main()
{
    int index;
    char words[200000][30];
    double t;

    srand(time(NULL));

    FILE *file = fopen("b.txt", "r");

    for (int i = 0; i < 200000; i++)
    {
        fscanf(file, "%s", words[i]);
    }
    printf("\n");

    fclose(file);

    struct bstree *tree = bstree_create(words[0], 0);

    for (int i = 1; i <= 200000; i++)
    {
        bstree_add(tree, words[i - 1], i - 1);
        if ((i % 10000) == 0)
        {
            index = rand() % (i - 1);
            t = wtime();
            bstree_lookup(tree, words[index]);
            printf("%s\n", words[index]);
            t = wtime() - t;
            printf("%d-ый элемент найден в дереве из %d элементов за время : %f\n", index, i, t);
            // t = wtime();
            // bstree_lookup(tree, words[index]);
            // printf("%s\n", words[index]);
            // t = wtime() - t;
            // printf("%d-ый элемент найден в дереве из %d элементов за время : %f\n", index, i, t);
        }
    }
    struct bstree *min = bstree_create(words[0], 0);
    min = bstree_min(tree);
    printf("%s\n", min->key);

    return 0;
}