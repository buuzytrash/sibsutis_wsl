#include <libgeom/geom.h>

int main()
{
    char *figure = malloc(4 * sizeof(char)), *str = malloc(4 * sizeof(char));
    char cir[] = {"circle"};
    int nof = 0, e = 1;

    FILE* file = fopen("output.txt", "r");

    printf("Enter the number of figures: ");
    scanf("%d", &nof);

    krug circle[nof];

    for (; e <= nof; e++) {
        fgets(str, 100, file);
        get_fig(str, figure);

        circle[e - 1].error = 0;

        if ((fig_check(figure, cir) == 1)) {
            get_numbers(&circle[e - 1], str);
            if ((circle[e - 1].r > 0)) {
                circle[e - 1].per = perimeter(&circle[e - 1]);
                circle[e - 1].s = area(&circle[e - 1]);

            } else {
                printf("%d) ERROR! Incorrect radius. Please, try again\n", e);
                circle[e - 1].r = 0;
                circle[e - 1].error = 1;
            }
        } else {
            printf("%d) ERROR! Incorrect name of figure\n", e);
            circle[e - 1].error = 1;
        }
        for (int i = 0; i < 6; i++) {
            figure[i] = 0;
        }
    }

    intersection_fig(&circle[0], nof);

    putchar('\n');
    for (e = 1; e <= nof; e++) {
        if (circle[e - 1].error == 0) {
            printf("%d) ", e);
            printf("%s(%.3f %.3f, %.3f)\nPerimeter: %.3f\nArea: %.3f\n "
                   "Intersects:\n   ",
                   figure,
                   circle[e - 1].p.x,
                   circle[e - 1].p.y,
                   circle[e - 1].r,
                   circle[e - 1].per,
                   circle[e - 1].s);
            for (long unsigned int i = 0; i < sizeof(circle[e - 1].intersection)
                         / sizeof(circle[e - 1].intersection[0]);
                 i++)
                printf("%d ", circle[e - 1].intersection[i]);
            putchar('\n');
        }
    }

    fclose(file);

    free(figure);
    free(str);
}