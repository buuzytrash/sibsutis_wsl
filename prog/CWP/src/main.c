#include <stdbool.h>
#include "integ.h"

int main(int argc, char **argv)
{
    if ((argc < 5) || (argc > 6))
    {
        fprintf(stderr, "%sPlease specify the file names!\n", RED);
        fprintf(stderr, "Basic usage: integrctrl –s –f data path\n");
        fprintf(stderr, "Basic usage: integrctrl –s -r –f data path\n");
        fprintf(stderr, "Basic usage: integrctrl –c –f data path\n%s",
                RESET);
        return -1;
    }

    int key, mode = NO_MODE, recursive = REC_OFF, file_count = FILE_MODE;
    int i, ch;
    char *data = NULL;
    char *path = NULL;

    while ((key = getopt(argc, argv, "scrf:")) != -1)
    {
        switch (key)
        {
        default:
        {
            fprintf(stderr,
                    "%sBasic usage: integrctrl –s –f data path\n",
                    RED);
            fprintf(stderr,
                    "Basic usage: integrctrl –s -r –f data path\n");
            fprintf(stderr,
                    "Basic usage: integrctrl –c –f data path\n%s",
                    RESET);
            return ER_MODE;
            break;
        }
        case 's':
        {
            if (mode != NO_MODE)
            {
                fprintf(stderr,
                        "%sYou're using keys -s and -c together or more than one\n%s",
                        RED, RESET);
                return ER_S_MODE;
            }
            mode = SAVE_MODE;
            break;
        }
        case 'c':
        {
            if (mode != NO_MODE)
            {
                fprintf(stderr,
                        "%sYou're using keys -s and -c together or more than one\n%s",
                        RED, RESET);
                return ER_C_MODE;
            }
            mode = CHECK_MODE;
            break;
        }
        case 'r':
        {
            if (recursive != REC_OFF)
            {
                fprintf(stderr, "%sYou use -r more than one time\n%s",
                        RED, RESET);
                return ER_R_MODE;
            }
            recursive = REC_ON;
            break;
        }
        case 'f':
        {
            if (file_count != FILE_MODE)
            {
                fprintf(stderr, "%sYou use -f more than one time\n%s",
                        RED, RESET);
                return ER_F_MODE;
            }
            if ((strcmp(optarg, "-f") == 0) || (strcmp(argv[optind], "-f") == 0))
            {
                fprintf(stderr, "%sYou use -f more than one time\n%s",
                        RED, RESET);
                return ER_F_MODE;
            }
            if ((strcmp(optarg, "-r") == 0) || (strcmp(argv[optind], "-r") == 0))
            {
                fprintf(stderr, "%sValue is key\n%s", RED, RESET);
                return ER_F_MODE;
            }
            if ((strcmp(optarg, "-s") == 0) || (strcmp(argv[optind], "-s") == 0))
            {
                fprintf(stderr, "%sValue is key\n%s", RED, RESET);
                return ER_F_MODE;
            }
            if ((strcmp(optarg, "-c") == 0) || (strcmp(argv[optind], "-c") == 0))
            {
                fprintf(stderr, "%sValue is key\n%s", RED, RESET);
                return ER_F_MODE;
            }
            if (!argv[optind])
            {
                fprintf(stderr,
                        "%sCould not find the path directory\n%s", RED,
                        RESET);
                return ER_F_MODE;
            }

            file_count++;
            data = optarg;
            path = argv[optind];
            break;
        }
        }
    }

    if (check_path(path))
    {
        return ER_PATH;
    }

    if ((mode == CHECK_MODE) && (recursive == REC_ON))
    {
        fprintf(stderr, "%sYou're using -r with -c%s\n", RED, RESET);
        return ER_MODE;
    }

    if (fopen(data, "r"))
    {
        fprintf(stdout, "%sYour data alredy is exist%s\n", RED, RESET);
        fprintf(stdout, "%sThis data will be rewrite, aru you shure?(Y/N/Q)%s\n", GREEN, RESET);
        do
        {
            scanf("%d", &ch);
            if (ch == 'y' || ch == 'Y')
            {
                fclose(f);
                break;
            }
            else if (ch == 'N' || ch == 'n')
            {
                data = realloc(data, sizeof(char) * (strlen(data) + 5));
                sprintf(data, "%s.new", data);
                fprintf(stdout, "%sNow your data name is %s%s\n%s", RED, WHITE, data, RESET);
                fclose(f);
                break;
            }
            else if (ch == 'q' || ch == 'Q')
            {
                fclose(f);
                return EXIT_SUCCESS;
            }
            printf("%d \n", ch);
        } while (true);
    }

    if (mode == SAVE_MODE)
    { // Save information
        f = fopen(data, "wb");
        fwrite(&recursive, sizeof(int), 1, f);

        save_dir_list(path, path, recursive);

        printf("%s%sSave is OK\n%s%s", YELLOW, _n, _n, RESET);
    }
    else if (mode == CHECK_MODE)
    { // Check infromation
        f = fopen(data, "rb");
        if (!f)
        {
            fprintf(stderr, "%sYour data is not exsist%s\n", RED, RESET);
            return ER_DATA;
        }

        fread(&recursive, sizeof(int), 1, f);

        struct stat buff;
        stat(data, &buff);
        int i;

        count = (buff.st_size - sizeof(int)) / sizeof(DATA);
        info = calloc(count, sizeof(DATA));

        for (i = 0; i < count; i++)
        {
            fread(&info[i], sizeof(DATA), 1, f);
        }

        if (strcmp(info[0].parent_dir, path) != 0)
        {
            fprintf(stderr, "%s Your origin dir is %s\"%s\"%s\n", WHITE, RED,
                    info[0].parent_dir, RESET);
            return ER_PATH;
        }

        check_dir_list(path, path, recursive);

        printf("%s%sCheck is OK\n%s%s", YELLOW, _n, _n, RESET);
    }
    else
    {
        fprintf(stderr, "%sIncorrect mode\n%s", RED, RESET);
        return ER_MODE;
    }

    for (i = 0; i < count; i++)
    {
        if (strcmp(info[i].name, "|") != 0)
            fprintf(stderr, "%s%s%s[%s] %sis DELETED\n%s", WHITE, info[i].name,
                    GREEN, info[i].type, RED, RESET);
    }

    free(info);
    fclose(f);
    return EXIT_SUCCESS;
}
