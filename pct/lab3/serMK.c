#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double
getrand ()
{
  return (double)rand () / RAND_MAX;
}
double
func (double x, double y)
{
  return ((x) / (pow (y, 2)));
}

double
wtime ()
{
  struct timespec ts;
  clock_gettime (CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1E-9;
}

const double PI = 3.14159265358979323846;
const int n = 100000000;
int
main (int argc, char **argv)
{
  int in = 0;
  double s = 0;
  double t = wtime ();
  for (int i = 0; i < n; i++)
    {
      double x = getrand () * PI; /* x in [0, pi] */
      double y = getrand ();      /* y in [0, sin(x)] */
      if (y <= sin (x))
        {
          in++;
          s += func (x, y);
        }
    }
  double v = PI * in / n;
  double res = v * s / in;
  printf ("Result: %.12f, n %d\n", res, n);
  t = wtime () - t;
  printf ("Elapsed time (sec.): %.6f\n", t);
  return 0;
}