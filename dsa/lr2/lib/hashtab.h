#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#ifndef __HASHTAB__
#define __HASHTAB__
#define HASHTAB_SIZE 200000
struct listnode
{
    char *key;
    int value;
    struct listnode *next;
};
unsigned int hashtab_hash(char *key);
unsigned int ELFHash(char *s);
void hashtab_init(struct listnode **hashtab);
void hashtab_add(struct listnode **hashtab, char *key, uint32_t value);
void hashtab_add2(struct listnode **hashtab, char *key, uint32_t value);
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key);
void hashtab_delete(struct listnode **hashtab, char *key);
double wtime();

#endif