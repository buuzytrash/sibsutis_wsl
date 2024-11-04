#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sys/time.h"

#define CAPACITY 100000

#ifndef __HASHTABLE__
#define __HASHTABLE__

unsigned int bernstein_hash(char *word);

typedef struct Ht_item Ht_item;

struct Ht_item
{
    char *key;
    char *value;
};

typedef struct LinkedList LinkedList;

struct LinkedList
{
    Ht_item *item;
    LinkedList *next;
};

typedef struct HashTable HashTable;

struct HashTable
{
    Ht_item **items;
    LinkedList **overflow_buckets;
    int size;
    int count;
    int collisions;
};

static LinkedList *allocate_list();

static LinkedList *linkedlist_insert(LinkedList *list, Ht_item *item);

static Ht_item *linkedlist_remove(LinkedList *list);

static void free_linkedlist(LinkedList *list);

static LinkedList **create_overflow_buckets(HashTable *table);

static void free_overflow_buckets(HashTable *table);

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