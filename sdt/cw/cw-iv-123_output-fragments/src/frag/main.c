#include <libfrag / frags.h>

int main(int argc, char* argv[])
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        print_usage();
        return 0;
    } else if (argc < 6 || argc > 7) {
        print_usage();
        return -1;
    }
    FILE* file;
    int mode = NO_MODE;
    int k, n;
    size_t b;
    if (argc == 6)
        file = fopen(argv[5], "r");
    else if (argc == 7)
        file = fopen(argv[6], "r");

    if (!file) {
        printf("Can't open file\n");
        return -1;
    }

    if (args(argc, argv, &mode) != 0)
        return -1;

    if (mode == BYTES) {
        n = atoi(argv[3]);
        b = atoi(argv[4]);
        bytes_frag(n, b, file);
        fclose(file);
    } else if (mode == LINES) {
        n = atoi(argv[3]);
        k = atoi(argv[4]);
        frag(n, k, file);
        fclose(file);
    }

    return 0;
}