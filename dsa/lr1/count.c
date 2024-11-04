#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>
// for storing the maximum element of input array
int k = 0;
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

/* Method to sort the array */
void count(uint32_t A[], uint32_t B[], int n)
{
    int c[k], t;
    for (int i = 0; i <= k; i++)
    {
        // инициализируем массив для подсчета
        c[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        // считаем, сколько раз появляется каждое число из массива
        // затем увеличиваем счетчик c[t], где t - число из массива
        t = A[i];
        c[t]++;
    }
    for (int i = 1; i <= k; i++)
    {
        // записывает в каждую ячейку с[i] число элементов, не превышающих i
        c[i] = c[i] + c[i - 1];
    }
    for (int i = 0; i < n; i++)
    {
        // помещаем массива a в массив b
        t = A[i];
        B[c[t]] = t;
        // дикрементируем значение счетчика на 1
        c[t] = c[t] - 1;
    }
}
int main()
{
    int n;

    printf("Введите количество элементов\n");
    scanf("%d", &n);
    uint32_t *a = NULL, *b = NULL;
    a = malloc(n * sizeof(uint32_t));
    b = malloc(n * sizeof(uint32_t));
    double time_1, time_2, ftime;
    for (int i = 0; i < n; i++)
    {
        a[i] = getrand(0, 100000);
        if (a[i] > k)
        {
            // находим максимальный элемент в массиве a
            k = a[i];
        }
    }
    time_1 = wtime();
    count(a, b, n);
    time_2 = wtime();
    ftime = time_2 - time_1;
    // for (int i = 1; i <= n; i++)
    // {
    //     printf("%d ", b[i]);
    // }
    free(a);
    free(b);

    printf("\n %f \n", ftime);

    return 0;
}