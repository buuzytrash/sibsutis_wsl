#include <stdio.h>
#include <stdlib.h>

typedef unsigned int (*hash)(char *word, int nbins);

unsigned int universal_hash1(char *s, int nbins)
{
    unsigned const char *us;
    unsigned int h;
    // srand(seed);
    int i = 0;
    h = 0;
    for (us = (unsigned const char *)s; *us; us++)
    {
        h += (unsigned int)((*us % nbins) * rand() % nbins);
    }
    return h % nbins;
}

unsigned int universal_hash2(char *s, int nbins)
{
    unsigned const char *us;
    unsigned int h;
    srand(seed);
    int i = 0;
    h = 0;
    for (us = (unsigned const char *)s; *us; us++)
    {
        h += (unsigned int)((*us % nbins) * rand() % nbins);
    }
    return h % nbins;
}
unsigned int naive_hash(char *word, int nbins)
{
    unsigned int h = 0;
    int c;
    while (c = *word++)
        h += c;
    return h % nbins;
}
unsigned int bernstein_hash(char *word, int nbins)
{
    unsigned int h = 5381;
    int c;
    while (c = *word++)
        h = 33 * h + c;
    return h % nbins;
}
unsigned int FNV_hash(char *word, int nbins)
{
    unsigned long h = 14695981039346656037lu;
    char c;
    while (c = *word++)
    {
        h = h * 1099511628211lu;
        h = h ^ c;
    }
    return h % nbins;
}

struct hui
{
    hash func;
};

int main()
{
    struct hui h1;
    printf("%d\n", h1.func);
    h1.func = universal_hash;
    h1.func("zhopa", 2);
    printf("%d %d\n", h1.func, universal_hash("zhopa", 2));
}