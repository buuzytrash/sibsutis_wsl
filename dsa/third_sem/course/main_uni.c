#include "hash_table_uni.h"
#include <time.h>
#include "sys/time.h"

#define DIC_SIZE 100000

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
    srand(time(NULL));

    HashTable *ht = create_table(CAPACITY);

    FILE *file = fopen("a.txt", "r");
    char *temp = malloc(sizeof(char));
    char **words = (char **)malloc((DIC_SIZE) * sizeof(char *));

    double t1, t2;

    for (int i = 0; i < DIC_SIZE; i++)
    {
        fscanf(file, "%s", temp);
        words[i] = (char *)malloc((strlen(temp) + 1) * sizeof(char));
        strcpy(words[i], temp);
    }

    int rand_index;
    for (int i = 0; i < CAPACITY; i++)
    {
        ht_insert(ht, words[i], words[i]);
        if (i % 5000 == 0)
        {
            rand_index = rand() % (i - 1);
            for (int j; j < 10000; j++)
            {
                t1 = wtime();
                ht_search(ht, words[rand_index]);
                t1 = wtime() - t1;
                t2 += t1;
            }
            t1 = t2 / 10000;

            printf("%f\n", t1);
        }
    }

    printf("%d %d %d\n", ht->size, ht->count, ht->collisions);

    for (int i = 0; i < DIC_SIZE; i++)
    {
        free(words[i]);
    }
    free(words);
    free(temp);
    free_table(ht);

    fclose(file);
    return 0;
}