#include "tries.h"

#define N 10000

int main()
{
    char words[N][100];
    FILE *file = fopen("words.txt", "r");
    FILE *rez = fopen("rez.txt", "w");

    for (int i = 0; i < N; i++)
    {
        fscanf(file, "%s", words[i]);
    }
    fclose(file);

    // struct trie *trie = trie_create();
    // int count = 0;

    // for (int i = 0; i < 10000; i++)
    // {
    //     trie = trie_insert(trie, words[i], words[N - i]);
    //     count++;
    // }

    struct trie *z_trie = trie_create();
    for (int i = 0; i < 15; i++)
    {
        z_trie = trie_insert(z_trie, words[i], words[N - i]);
    }
    trie_print(z_trie, 0, rez);
    z_trie = trie_delete(z_trie, "enliven");
    z_trie = trie_delete(z_trie, "miaow");
    for (int i = 0; i < 20; i++)
        fprintf(rez, "--");
    printf("\n");
    trie_print(z_trie, 0, rez);
    printf("%d\n", trie_lookup(z_trie, "enliven"));
    printf("%d\n", trie_lookup(z_trie, "miaow"));

    // printf("%d\n", count);
}