#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>
#include <stdlib.h>
// app2

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
};

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
};

void bubble(uint32_t array[], int n)
{
    int c = 0, i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (array[i] < array[j])
            {
                c = array[i];
                array[i] = array[j];
                array[j] = c;
            }
        }
    }
};

int main()
{
    int n, i;
    printf("Введите количество элементов: ");
    scanf("%d", &n);
    uint32_t *a = NULL;
    a = malloc(n * sizeof(uint32_t));
    double time_1, time_2, ftime;

    for (i = 0; i < n; i++)
    {
        a[i] = getrand(0, 100000);
    }

    time_1 = wtime();
    bubble(a, n);
    time_2 = wtime();
    ftime = time_2 - time_1;

    // for (i = 0; i < n; i++)
    // {
    //     printf("%d ", a[i]);
    // }
    printf("\n%f\n", ftime);

    return 0;
}