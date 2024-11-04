#include <iostream>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define threshold 1000
#define N 100000000

void
partition (int *v, int &i, int &j, int low, int high)
{
  i = low;
  j = high;
  int pivot = v[(low + high) / 2];
  do
    {
      while (v[i] < pivot)
        i++;
      while (v[j] > pivot)
        j--;
      if (i <= j)
        {
          std::swap (v[i], v[j]);
          i++;
          j--;
        }
    }
  while (i <= j);
}

void
quicksort (int *v, int low, int high)
{
  int i, j;
  partition (v, i, j, low, high);
  if (low < j)
    quicksort (v, low, j);
  if (i < high)
    quicksort (v, i, high);
}

void
quicksort_un_tasks (int *v, int low, int high)
{
  int i, j;
  partition (v, i, j, low, high);
  if (high - low < threshold || (j - low < threshold || high - i < threshold))
    {
      if (low < j)
        quicksort_un_tasks (v, low, j);
      if (i < high)
        quicksort_un_tasks (v, i, high);
    }
  else
    {
#pragma omp task                                                              \
    untied // Открепить задачу от потока (задачу может выполнять любой поток)
      {
        quicksort_un_tasks (v, low, j);
      }
      quicksort_un_tasks (v, i, high);
    }
}

void
quicksort_tasks (int *v, int low, int high)
{
  int i, j;
  partition (v, i, j, low, high);
  if (high - low < threshold || (j - low < threshold || high - i < threshold))
    {
      if (low < j)
        quicksort_tasks (v, low, j);
      if (i < high)
        quicksort_tasks (v, i, high);
    }
  else
    {
#pragma omp task
      {
        quicksort_tasks (v, low, j);
      }
      quicksort_tasks (v, i, high);
    }
}

int
main ()
{
  int *arr1 = (int *)malloc (sizeof (int) * N),
      *arr2 = (int *)malloc (sizeof (int) * N);
  double t1, t2;
  for (int i = 0; i < N; i++)
    {
      arr1[i] = rand ();
      arr2[i] = arr1[i];
    }

  t1 = -omp_get_wtime ();
  quicksort (arr1, 0, N - 1);
  t1 += omp_get_wtime ();

#if 0
  t2 = -omp_get_wtime ();
#pragma omp parallel
  {
#pragma omp single
    quicksort_tasks (arr2, 0, N - 1);
  }
  t2 += omp_get_wtime ();
#endif

#if 1
  t2 = -omp_get_wtime ();
#pragma omp parallel
  {
#pragma omp single
    quicksort_un_tasks (arr2, 0, N - 1);
  }
  t2 += omp_get_wtime ();
#endif

  bool check{ true };
  int n = 0;

  for (int i = 0; i < N; ++i)
    {
      if (arr1[i] != arr2[i])
        {
          check = false;
        }
      else
        n++;
    }
  free (arr1);
  free (arr2);

  printf ("Check: %s %d\n", (check) ? "True" : "False", n);

  printf ("Default ver: %lf \nParallel ver: %lf\n Speedup: %lf\n", t1, t2,
          t1 / t2);

  return 0;
}