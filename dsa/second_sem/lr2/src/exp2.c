#include "bstree.h"
#include "hashtab.h"

int main()
{
    int index, N = 0;
    char words[200000][30];
    double t;

    scanf("%d", &N);

    srand(time(NULL));

    FILE *file = fopen("a.txt", "r");
    FILE *exp2 = fopen("exp2.txt", "a");

    for (int i = 0; i < 200000; i++)
    {
        fscanf(file, "%s", words[i]);
    }
    printf("\n");

    fclose(file);

    struct bstree *tree = bstree_create(words[0], 0);
    struct listnode **hashtab = malloc(sizeof(struct listnode) * HASHTAB_SIZE);
    fprintf(exp2, "%d ", N);
    t = wtime();
    for (int i = 1; i <= N; i++)
    {

        bstree_add(tree, words[i - 1], i - 1);
    }
    t = wtime() - t;
    printf("Время заполнения bstree из %d элементов: %f\n", N, t);
    fprintf(exp2, "%f ", t);

    t = wtime();
    for (int i = 1; i <= N; i++)
    {
        hashtab_add(hashtab, words[i - 1], i - 1);
    }
    t = wtime() - t;
    printf("Время заполнения hashtab из %d элементов: %f\n", N, t);
    fprintf(exp2, "%f\n", t);
    return 0;
}