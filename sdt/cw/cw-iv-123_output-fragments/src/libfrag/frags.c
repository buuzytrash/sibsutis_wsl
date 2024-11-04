#include "frags.h"

void frag(int instr, int nol, FILE* file)
{
    char* str = malloc(sizeof(char) * 1000);
    int tag;
    int ftag = instr + nol - 1;

    for (tag = 1; tag <= ftag; tag++) {
        if (tag >= instr && tag <= ftag) {
            fgets(str, 1000, file);
            printf("%d. %s", tag, str);
        } else
            fgets(str, 1000, file);
    }

    free(str);
}

void bytes_frag(int instr, size_t bytes, FILE* file)
{
    char* str = malloc(sizeof(char) * 10000);
    int tag = 1;
    while (tag != instr) {
        tag++;
        fgets(str, 10000, file);
    }

    if (fread(str, sizeof(char), bytes, file) == bytes)
        printf("%s\n", str);

    free(str);
}

void print_usage()
{
    printf("Usage: ./frag -n [number of initial string] -k [nubmer of "
           "lines] [FILE]...\n       ./frag -n [number of initial string] "
           "-b [nubmer of "
           "bytes] [FILE]...\n       ./frag -n [number of initial string] "
           "-b [nubmer of "
           "bytes] -v [FILE]...\n       ./frag --help - display this "
           "help\n");
}

int args(int argc, char* argv[], int* mode)
{
    int key;
    while ((key = getopt(argc, argv, "nbkv:")) != -1) {
        switch (key) {
        default: {
            printf("Incorrect parameters\n");
            print_usage();
            return -1;
            break;
        }
        case 'v': {
            printf("==>%s<==\n", argv[6]);
            return 0;

            break;
        }

        case 'n': {
            break;
        }
        case 'b': {
            if (*mode != NO_MODE) {
                printf("You use -b and -k together. Please, try again\n");
                return -1;
            }

            *mode = BYTES;

            break;
        }
        case 'k': {
            if (*mode != NO_MODE) {
                printf("You use -b and -k together. Please, try again\n");
                return -1;
            }
            *mode = LINES;

            break;
        }
        }
    }

    return 0;
}