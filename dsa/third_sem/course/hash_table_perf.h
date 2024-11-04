#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sys/time.h"

#define CAPACITY 100000
#define LOCAL_CAPACITY 10

#ifndef __HASHTABLE__
#define __HASHTABLE__

unsigned long hash_function(char *str);
unsigned int FNV_hash(char *word);

typedef struct Ht_item Ht_item;

struct Ht_item
{
    char *key;
    char *value;
};

typedef struct HashTable HashTable;

struct HashTable
{
    Ht_item **items;
    HashTable **LocalHT;
    int size;
    int count;
};

HashTable *create_local(int size);

Ht_item *create_item(char *key, char *value);

HashTable *create_table(int size);

void free_item(Ht_item *item);

void free_table(HashTable *table);

void handle_collision(HashTable *table, unsigned long index, Ht_item *item);

void ht_insert(HashTable *table, char *key, char *value);

char *ht_search(HashTable *table, char *key);

void ht_delete(HashTable *table, char *key);

void print_search(HashTable *table, char *key);

void print_table(HashTable *table);

#endif