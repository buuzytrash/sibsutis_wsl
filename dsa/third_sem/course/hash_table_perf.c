#include "hash_table_perf.h"

unsigned long hash_function(char *str)
{
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

unsigned int FNV_hash(char *word)
{
    unsigned long h = 14695981039346656037lu;
    char c;
    while (c = *word++)
    {
        h = h * 1099511628211lu;
        h = h ^ c;
    }
    return h % LOCAL_CAPACITY;
}

Ht_item *create_item(char *key, char *value)
{
    Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
    item->key = (char *)malloc(strlen(key) + 1);
    item->value = (char *)malloc(strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

HashTable *create_table(int size)
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item **)calloc(table->size, sizeof(Ht_item *));
    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;

    table->LocalHT = (HashTable **)malloc(sizeof(HashTable *));

    return table;
}

HashTable *create_local(int size)
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item **)calloc(table->size, sizeof(Ht_item *));
    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;
    return table;
}

void free_item(Ht_item *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable *table)
{
    for (int i = 0; i < table->size; i++)
    {
        Ht_item *item = table->items[i];
        if (item != NULL)
            free_item(item);
    }
    for (int i = 0; i < table->size; i++)
    {
        HashTable *ht = table->LocalHT[i];
        if (ht != NULL)
            free_table(ht);
    }

    free(table->LocalHT);
    free(table->items);
    free(table);
}

void handle_collision(HashTable *table, unsigned long index, Ht_item *item)
{
    table->LocalHT[index] = create_local(LOCAL_CAPACITY);
    table->items[index] = NULL;
    unsigned int new_index = FNV_hash(item->key);
    table->LocalHT[index]->items[new_index] = item;
    table->LocalHT[index]->count++;
    return;
}

void ht_insert(HashTable *table, char *key, char *value)
{
    Ht_item *item = create_item(key, value);

    unsigned int index;
    index = hash_function(key);

    Ht_item *current_item = table->items[index];
    HashTable *current_table = table->LocalHT[index];

    if (current_item == NULL)
    {
        if (table->count == table->size)
        {
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }

        table->items[index] = item;
        table->count++;
    }

    else
    {
        if ((strcmp(current_item->key, key) == 0))
        {
            strcpy(table->items[index]->value, value);
            return;
        }

        else
        {
            handle_collision(table, index, item);
            return;
        }
    }
}