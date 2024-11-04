#include "hashtab.h"

int main()
{
    int index, k1 = 0, k2 = 0;
    char words[200000][30];
    double t3, t4, t1, t2;

    srand(time(NULL));

    FILE *file = fopen("b.txt", "r");
    FILE *exp6 = fopen("exp6.txt", "a");

    for (int i = 0; i < 200000; i++)
    {
        fscanf(file, "%s", words[i]);
    }
    printf("\n");
    fclose(file);

    struct listnode **hashtab1 = malloc(sizeof(struct listnode) * HASHTAB_SIZE);
    struct listnode **hashtab2 = malloc(sizeof(struct listnode) * HASHTAB_SIZE);
    hashtab_init(hashtab1);
    hashtab_init(hashtab2);
    for (int i = 1; i <= 200000; i++)
    {
        hashtab_add(hashtab1, words[i - 1], i - 1);
        hashtab_add2(hashtab2, words[i - 1], i - 1);

        if ((i % 10000) == 0)
        {
            fprintf(exp6, "%d ", i);
            index = rand() % (i - 1);
            for (int j = 0; j < 1000; j++)
            {
                t1 = wtime();
                hashtab_lookup(hashtab1, words[index]);
                t1 = wtime() - t1;
                t3 += t1;
            }
            t1 = t3 / 1000;

            for (int j = 0; j < 1000; j++)
            {
                t2 = wtime();
                hashtab_lookup(hashtab2, words[index]);
                t2 = wtime() - t2;
                t4 += t2;
            }
            t2 = t4 / 1000;

            for (int j = 0; j < 200000; j++)
            {
                if (hashtab1[j] == NULL)
                {
                    k1++;
                }
                if (hashtab2[j] == NULL)
                {
                    k2++;
                }
            }

            printf("%s\n", words[index]);

            printf("%d-ый элемент найден в hashtab1 из %d элементов за время : %f\n", index, i, t1);
            fprintf(exp6, "%f ", t1);
            k1 = k1 - (HASHTAB_SIZE - i);
            fprintf(exp6, "%d ", k1);
            k1 = 0;

            printf("%d-ый элемент найден в hashtab2 из %d элементов за время : %f\n", index, i, t2);
            fprintf(exp6, "%f ", t2);
            k2 = k2 - (HASHTAB_SIZE - i);
            fprintf(exp6, "%d\n", k2);
            k2 = 0;
        }
    }

    fclose(exp6);

    return 0;
}