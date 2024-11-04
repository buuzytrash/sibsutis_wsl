#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum OPTIONS
{
    NO_OPTION,
    BYTES,
    QUIET,
    VERBOSE
};

void head(int instr, int nol, FILE *file, int *option) // instr - initial string, nol - number of lines
{
    char *str = malloc(sizeof(char) * 10000);
    int tag;
    int ftag = instr + nol - 1;

    for (tag = 1; tag <= ftag; tag++)
    {
        if (tag >= instr && tag <= ftag)
        {
            fgets(str, 10000, file);
            printf("%d. %s", tag, str);
        }
        else
            fgets(str, 10000, file);
    }

    free(str);
}

int main(int argc, char *argv[])
{
    int option = NO_OPTION;
    if (argc == 4)
    {
        if ((atoi(argv[1]) == 0) || (atoi(argv[2]) == 0))
        {
            printf("Incorrect parameters\n Use ./frag --help\n");
            exit(-1);
        }
        int N = atoi(argv[1]);
        int K = atoi(argv[2]);

        FILE *file = fopen(argv[3], "r");
        if (!file)
        {
            printf("Error! The specified file does not exist\nPlease, try again\n");
            return -1;
        }
        else
            head(N, K, file);
        fclose(file);
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "--help") == 0)
        {
            printf("Usage: ./frag N K... [FILE]...\n N - initial line\n K - number of lines\n");
            printf("\n--help  display this help and exit\n");
        }
        else
        {
            printf("Incorrect parameters\n Use ./frag --help\n");
        }
    }
    else if (argc < 4)
    {
        printf("Incorrect parametres\n Use ./frag --help\n");
    }
}