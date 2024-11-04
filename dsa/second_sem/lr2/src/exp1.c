#include "bstree.h"
#include "hashtab.h"

int main()
{
    int index;
    char words[200000][30];
    double t3, t4, t1, t2;

    srand(time(NULL));

    FILE *file = fopen("a.txt", "r");
    FILE *exp1 = fopen("exp1.txt", "a");

    for (int i = 0; i < 200000; i++)
    {
        fscanf(file, "%s", words[i]);
    }
    printf("\n");
    fclose(file);

    struct bstree *tree = bstree_create(words[0], 0);
    struct listnode **hashtab = malloc(sizeof(struct listnode) * HASHTAB_SIZE);
    hashtab_init(hashtab);
    for (int i = 1; i <= 200000; i++)
    {
        bstree_add(tree, words[i - 1], i - 1);
        hashtab_add(hashtab, words[i - 1], i - 1);
        if ((i % 10000) == 0)
        {
            fprintf(exp1, "%d ", i);
            index = rand() % (i - 1);
            for (int j = 0; j < 1000; j++)
            {
                t1 = wtime();
                bstree_lookup(tree, words[index]);
                t1 = wtime() - t1;
                t3 += t1;
            }
            t1 = t3 / 1000;

            for (int j = 0; j < 1000; j++)
            {
                t2 = wtime();
                hashtab_lookup(hashtab, words[index]);
                t2 = wtime() - t2;
                t4 += t2;
            }
            t2 = t4 / 1000;

            printf("%s\n", words[index]);
            printf("%d-ый элемент найден в дереве из %d элементов за время : %f\n", index, i, t1);
            printf("%d-ый элемент найден в хэш-таблице из %d элементов за время : %f\n", index, i, t2);
            fprintf(exp1, "%f ", t1);
            fprintf(exp1, "%f\n", t2);
        }
    }

    TraversInOrder(tree);

    fclose(exp1);
    // struct bstree *min = bstree_create(words[0], 0);
    // min = bstree_min(tree);
    // printf("%s\n", min->key);

    return 0;
}