#include "geom.h"

char* get_fig(char* str, char* figure)
{
    char cir[] = {"circle"};
    int i;
    if ((strstr(str, cir) != NULL) || (strstr(figure, cir) != NULL)) {
        if (strcmp(figure, cir) != 0) {
            strcpy(figure, "");
            i = 0;
        }
        while (str[i] != '\0') {
            if ((str[i] >= 65 && str[i] <= 90)
                || (str[i] >= 97 && str[i] <= 122))

                strncat(figure, &str[i], 1);
            else
                break;
            i++;
        };
    }
    return figure;
}
void get_numbers(krug* circle, char* str)
{
    char cir[] = {"circle"};
    char *cor1 = malloc(4 * sizeof(char)), *cor2 = malloc(4 * sizeof(char)),
         *rad = malloc(4 * sizeof(char)), *num = malloc(4 * sizeof(char));
    int i = 0;
    if (strstr(str, cir) != NULL) {
        while (str[i] != ')') {
            if (str[i] == '-')
                strncat(num, &str[i], 1);
            if ((str[i] >= 48 && str[i] <= 57) || str[i] == '.')
                strncat(num, &str[i], 1);
            i++;
            if (str[i] == ' ' && str[i - 1] != ',') {
                strcpy(cor1, num);
                strcpy(num, "");
                circle->p.x = atof(cor1);
            }
            if (str[i] == ',') {
                strcpy(cor2, num);
                strcpy(num, "");
                circle->p.y = atof(cor2);
            }
            if (str[i] == ')') {
                strcpy(rad, num);
                strcpy(num, "");
                circle->r = atof(rad);
                        }
            if (str[i] == ')'
                && (((str[i + 1] >= 48) && (str[i + 1]) <= 90)
                    || ((str[i + 2] >= 97) && (str[i + 2] <= 122)))) {
                printf("ERROR! Incorrect data\n");
                circle->error = 1;
            }
        }
    }

    free(cor1);
    free(cor2);
    free(rad);
    free(num);
}

int fig_check(char* figure, char* cir)
{
    int yes = 0;
    for (int i = 0; i < 6; i++) {
        if (figure[i] == cir[i])
            yes = 1;
    }
    if ((figure[6] >= 65 && figure[6] <= 90)
        || (figure[6] >= 97 && figure[6] <= 122)) {
        yes = 0;
    }
    return yes;
}

double perimeter(krug* circle)
{
    double p = 2 * M_PI * circle->r;
    return p;
}
double area(krug* circle)
{
    double s = M_PI * pow(circle->r, 2);
    return s;
}

int intersection_fig(krug* circle, int nof)
{
    int i, j, n;
    for (i = 0; i < nof; i++) {
        n = 0;
        for (j = nof - 1; j > -1; j--) {
            if (circle[i].error == 0 && circle[j].error == 0)
                if (fabs(circle[i].p.x - circle[j].p.x)
                    <= (circle[i].r + circle[j].r)) {
                    if (fabs(circle[i].p.y - circle[j].p.y)
                        <= (circle[i].r + circle[j].r)) {
                        if (i != j) {
                            circle[i].intersection[n] = j + 1;
                            n++;
                        }
                    }
                }
        }
    }

    return 0;
}
