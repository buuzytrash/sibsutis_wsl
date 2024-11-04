#include <inttypes.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <util/xmalloc.h>
// #define n 15000
// #define m 15000

double
wtime ()
{
  struct timespec ts;
  clock_gettime (CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1E-9;
}

void
matrix_vector_product (double *a, double *b, double *c, int m, int n)
{
  for (int i = 0; i < m; i++)
    {
      c[i] = 0.0;
      for (int j = 0; j < n; j++)
        c[i] += a[i * n + j] * b[j];
    }
}

void
matrix_vector_product_omp (double *a, double *b, double *c, int m, int n)
{
#pragma omp parallel // num_threads(6)
  {
    int nthreads = omp_get_num_threads ();
    printf ("%d\n", nthreads);
    int threadid = omp_get_thread_num ();
    int items_per_thread = m / nthreads;
    int lb = threadid * items_per_thread;
    int ub
        = (threadid == nthreads - 1) ? (m - 1) : (lb + items_per_thread - 1);
    for (int i = lb; i <= ub; i++)
      {
        c[i] = 0.0;
        for (int j = 0; j < n; j++)
          c[i] += a[i * n + j] * b[j];
      }
  }
}

void
run_serial (int n, int m)
{
  double *a, *b, *c;
  a = malloc (sizeof (*a) * m * n);
  b = malloc (sizeof (*b) * n);
  c = malloc (sizeof (*c) * m);
  for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
        a[i * n + j] = i + j;
    }
  for (int j = 0; j < n; j++)
    b[j] = j;
  double t = wtime ();
  matrix_vector_product (a, b, c, m, n);
  t = wtime () - t;
  printf ("Elapsed time (serial): %.6f sec.\n", t);
  free (a);
  free (b);
  free (c);
}

void
run_parallel (int n, int m)
{
  double *a, *b, *c;
  // Allocate memory for 2-d array a[m, n]
  a = malloc (sizeof (*a) * m * n);
  b = malloc (sizeof (*b) * n);
  c = malloc (sizeof (*c) * m);
  for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
        a[i * n + j] = i + j;
    }
  for (int j = 0; j < n; j++)
    b[j] = j;
  double t = wtime ();
  matrix_vector_product_omp (a, b, c, m, n);
  t = wtime () - t;
  printf ("Elapsed time (parallel): %.6f sec.\n\n", t);
  free (a);
  free (b);
  free (c);
}

int
main (int argc, char **argv)
{
  int n = 15000, m = 15000;

  // for (; n < 40000; n += 5000, m += 5000)
  //   {
  printf ("Matrix-vector product (c[m] = a[m, n] * b[n]; m = %d, n = %d)\n", m,
          n);
  printf ("Memory used: %" PRIu64 " MiB\n",
          ((m * n + m + n) * sizeof (double)) >> 20);
  run_parallel (n, m);
  // run_serial (n, m);
  // }
  return 0;
}