#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum MODES
{
    NO_MODE,
    LINES,
    BYTES
};
void frag(int instr, int nol, FILE *file)
{
    char *str = malloc(sizeof(char) * 1000);
    int tag;
    int ftag = instr + nol - 1;

    for (tag = 1; tag <= ftag; tag++)
    {
        if (tag >= instr && tag <= ftag)
        {
            fgets(str, 1000, file);
            printf("%d. %s", tag, str);
        }
        else
            fgets(str, 1000, file);
    }

    free(str);
}

void bytes_frag(int instr, int bytes, FILE *file)
{
    char *str = malloc(sizeof(char) * 10000);
    int tag = 1;
    while (tag != instr)
    {
        tag++;
        fgets(str, 10000, file);
    }

    if (fread(str, sizeof(char), bytes, file) == bytes)
        printf("%s\n", str);

    free(str);
}

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        printf("Usage: ./frag -n [number of initial string] -k [nubmer of "
               "lines] [FILE]...\n       ./frag -n [number of initial string] "
               "-b [nubmer of "
               "bytes] [FILE]...\n       ./frag -n [number of initial string] "
               "-b [nubmer of "
               "bytes] -v [FILE]...\n       ./frag --help - display this "
               "help\n");
        return 0;
    }
    else if (argc < 6 || argc > 7)
    {
        printf("Usage: ./frag -n [number of initial string] -k [nubmer of "
               "lines] [FILE]...\n       ./frag -n [number of initial string] "
               "-b [nubmer of "
               "bytes] [FILE]...\n       ./frag -n [number of initial string] "
               "-b [nubmer of "
               "bytes] -v [FILE]...\n");
        return -1;
    }
    FILE *file;
    int key, mode = NO_MODE;
    int k, b, n;
    if (argc == 6)
        file = fopen(argv[5], "r");
    else if (argc == 7)
        file = fopen(argv[6], "r");

    if (!file)
    {
        printf("Can't open file\n");
        return -1;
    }

    while ((key = getopt(argc, argv, "nbkv:")) != -1)
    {
        switch (key)
        {
        default:
        {
            printf("Incorrect parameters\n");
            printf("Usage: ./frag -n [number of initial string] -k [nubmer of "
                   "lines] [FILE]...\n       ./frag -n [number of initial "
                   "string] "
                   "-b [nubmer of "
                   "bytes] [FILE]...\n       ./frag -n [number of initial "
                   "string] "
                   "-b [nubmer of "
                   "bytes] -v [FILE]...\n");
            return -1;
            break;
        }
        case 'v':
        {
            printf("==>%s<==\n", argv[6]);

            break;
        }

        case 'n':
        {
            n = atoi(argv[2]);

            break;
        }
        case 'b':
        {
            if (mode != NO_MODE)
            {
                printf("You use -b and -k together. Please, try again\n");
                return -1;
            }
            b = atoi(argv[4]);
            mode = BYTES;

            break;
        }
        case 'k':
        {
            if (mode != NO_MODE)
            {
                printf("You use -b and -k together. Please, try again\n");
                return -1;
            }
            k = atoi(argv[4]);
            mode = LINES;

            break;
        }
        }
    }

    if (mode == BYTES)
    {
        bytes_frag(n, b, file);
        fclose(file);
    }
    else if (mode == LINES)
    {
        frag(n, k, file);
        fclose(file);
    }

    return 0;
}