#include "hash_table_perf.h"
#include <time.h>
#include "sys/time.h"

#define DIC_SIZE 100000

int main()
{
    srand(time(NULL));

    HashTable *ht = create_table(CAPACITY);

    FILE *file = fopen("a.txt", "r");
    char *temp = malloc(sizeof(char));
    char **words = (char **)malloc((DIC_SIZE) * sizeof(char *));

    for (int i = 0; i < DIC_SIZE; i++)
    {
        fscanf(file, "%s", temp);
        words[i] = (char *)malloc((strlen(temp) + 1) * sizeof(char));
        strcpy(words[i], temp);
    }

    for (int i = 0; i < CAPACITY; i++)
    {
        ht_insert(ht, words[i], words[i]);
    }

    printf("%d %d \n", ht->size, ht->count);

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