#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>
#include <stdlib.h>
// app
void merge(uint32_t a[], int low, int mid, int high, int n)
{

    int l = low;     // начало левого подмассива
    int r = mid + 1; // начало правого подмассива
    int i = low;

    uint32_t *b = NULL;
    b = malloc(n * sizeof(uint32_t)); // копия массива a
    for (; low <= high; low++)
    {
        b[low] = a[low];
    }
    while (l <= mid && r <= high)
    {
        if (b[l] <= b[r])
        {
            a[i] = b[l];
            l++;
        }
        else
        {
            a[i] = b[r];
            r++;
        }
        i++;
    }
    while (l <= mid)
    {
        a[i] = b[l]; // копируем элементы из левого подмассива
        l++;
        i++;
    }
    while (r <= high)
    {
        a[i] = b[r]; // копируем элементы из правого подмассива
        r++;
        i++;
    }

    free(b);
}

void merge_sort(uint32_t a[], int low, int high, int n)
{
    // делим массив на 2 максимально равные части
    int mid = low + (high - low) / 2;

    if (low < high)
    {
        merge_sort(a, low, mid, n);
        merge_sort(a, mid + 1, high, n);
        merge(a, low, mid, high, n);
    }
}

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

int main()
{
    int n;
    printf("Введите количество элементов в массиве: \n");
    scanf("%d", &n);

    uint32_t *a = NULL;
    int i;
    a = malloc(n * sizeof(uint32_t));

    for (i = 0; i < n; i++)
        a[i] = getrand(0, 100000);

    double time_1 = wtime();
    merge_sort(a, 0, n - 1, n);
    double time_2 = wtime();
    double ftime = time_2 - time_1;

    // for (i = 0; i < n; i++)
    //     printf("%d ", a[i]);

    printf("время сортировки: %f\n", ftime);

    return 0;
}
