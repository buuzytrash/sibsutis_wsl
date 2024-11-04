#include <math.h>

#include <stdio.h>

double x[11], f[11];

double
Eitken (double X, int n)

{

  double Y[51][51];

  for (int j = 0; j <= n; j++)
    {

      Y[j][j] = f[j];

      for (int i = j - 1; i >= 0; i--)

        Y[i][j] = 1 / (x[j] - x[i])
                  * ((X - x[i]) * Y[i + 1][j] - (X - x[j]) * Y[i][j - 1]);
    }

  return Y[0][n];
}

int
main ()

{

  double X = 2.5600;

  x[0] = 1.0000;
  f[0] = 1.0000;

  x[1] = 2.0000;
  f[1] = 1.4142;

  x[2] = 3.0000;
  f[2] = 1.7321;

  x[3] = 4.0000;
  f[3] = 2.0000;

  // x[4] = 2.1920; f[4] = -0.1849;

  // x[5] = 2.4232; f[5] = -0.3474;

  // x[6] = 3.6152; f[6] = 2.5986;

  // x[7] = 3.6800; f[7] = 3.0616;

  // x[8] = 4.5024; f[8] = 13.1676;

  // x[9] = 5.1672; f[9] = 28.6035;

  // x[10] = 6.0424; f[10] = 62.0144;

  printf ("Eitken: f(%f) = %f ", X, Eitken (X, 4));
  return 0;
}