#include <ctest.h>
#include <libfrag/frags.h>

CTEST(arguments, test_right_arguments_BYTES)
{
    int mode = NO_MODE;

    int argc = 6;
    char** argv;
    argv = malloc(6 * sizeof(char*));
    for (int i = 0; i < 6; i++)
        argv[i] = malloc(20);

    strcpy(argv[0], "./bin/frag");
    strcpy(argv[1], "-n");
    strcpy(argv[2], "14");
    strcpy(argv[3], "-b");
    strcpy(argv[4], "100");
    strcpy(argv[5], "robot.txt");

    args(argc, argv, &mode);
    for (int i = 0; i < 6; i++)
        free(argv[i]);
    free(argv);
    ASSERT_EQUAL(BYTES, mode);
}

CTEST(arguments, test_right_arguments_LINES)
{
    int mode = NO_MODE;

    int argc = 6;
    char** argv;
    argv = malloc(6 * sizeof(char*));
    for (int i = 0; i < 6; i++)
        argv[i] = malloc(20);

    strcpy(argv[0], "./bin/frag");
    strcpy(argv[1], "-n");
    strcpy(argv[2], "14");
    strcpy(argv[3], "-k");
    strcpy(argv[4], "100");
    strcpy(argv[5], "robot.txt");

    args(argc, argv, &mode);

    for (int i = 0; i < 6; i++)
        free(argv[i]);
    free(argv);
    ASSERT_EQUAL(LINES, mode);
}

CTEST(arguments, test_wrong)
{
    int mode = NO_MODE;

    int argc = 6;
    char** argv;
    argv = malloc(6 * sizeof(char*));
    for (int i = 0; i < 6; i++)
        argv[i] = malloc(20);

    strcpy(argv[0], "./bin/frag");
    strcpy(argv[1], "-n");
    strcpy(argv[2], "14");
    strcpy(argv[3], "-l");
    strcpy(argv[4], "3");
    strcpy(argv[5], "robot.txt");
    freopen("OUTPUT", "w+", stdout);
    int f = args(argc, argv, &mode);
    freopen("/dev/tty", "w+", stdout);
    for (int i = 0; i < 6; i++)
        free(argv[i]);
    free(argv);

    ASSERT_EQUAL(-1, f);
}
CTEST(arguments, test_right_arguments_verbase)
{
    int mode = NO_MODE;

    int argc = 7;
    char** argv;
    argv = malloc(7 * sizeof(char*));
    for (int i = 0; i < 7; i++)
        argv[i] = malloc(20);

    strcpy(argv[0], "./bin/frag");
    strcpy(argv[1], "-n");
    strcpy(argv[2], "14");
    strcpy(argv[3], "-k");
    strcpy(argv[4], "8");
    strcpy(argv[5], "-v");
    strcpy(argv[6], "robot.txt");

    freopen("OUTPUT", "w+", stdout);
    args(argc, argv, &mode);
    freopen("/dev/tty", "w+", stdout);
    for (int i = 0; i < 7; i++)
        free(argv[i]);
    free(argv);
    ASSERT_EQUAL(LINES, mode);
}