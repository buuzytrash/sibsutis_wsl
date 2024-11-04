#include <inttypes.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _POSIX_C_SOURCE 1

double
func (double x, double y)
{
  return ((x) / (pow (y, 2)));
}

double
getrand (unsigned int *seed)
{
  return (double)rand_r (seed) / RAND_MAX;
}

int
main (int argc, char **argv)
{

  double t = omp_get_wtime ();
  const double PI = 3.14159265358979323846;
  const int n = 100000000;
  printf ("Numerical integration by Monte Carlo method: n = %d\n", n);

  int in = 0;
  double s = 0;
#pragma omp parallel
  {
    double s_loc = 0;
    int in_loc = 0;
    unsigned int seed = omp_get_thread_num ();
#pragma omp for nowait
    for (int i = 0; i < n; i++)
      {
        double x = getrand (&seed);
        double y = 2 + getrand (&seed) * 3;
        if (y < 5 && y > 2)
          {
            in_loc++;
            s_loc += func (x, y);
          }
      }
#pragma omp atomic
    s += s_loc;
#pragma omp atomic
    in += in_loc;
  }
  printf ("%f %d\n", s, in);

  double v = PI * in / n;
  double res = v * s / in;
  printf ("Result: %.12f, n %d\n", res, n);
  t = omp_get_wtime () - t;
  printf ("Elapsed time (sec.): %.6f\n", t);

  return 0;
}