#include <math.h>
#include <stdio.h>

const double a_E = 0.999, a_I = 0.999, k = 0.042, p = 0.952, B = 0.999,
             mu = 0.0188, c_isol = 0, y = 0, a = 1;

double
function_c (double c_isol)
{
  return 1 + c_isol * (1 - 2 / 5 * a);
}

double
function_S (double S, double E, double I, double R, double N)
{
  return -1 * function_c (c_isol) * S / N * (a_I * I + a_E * E) + y * R;
}

double
delta_S (double S, double E, double I, double R, double N, double h)
{
  return h * function_S (S + h / 2 * function_S (S, E, I, R, N), E, I, R, N);
}

double
function_E (double S, double E, double I, double N)
{
  return function_c (c_isol) * S / N * (a_I * I + a_E * E) - (k + p) * E;
}

double
delta_E (double S, double E, double I, double N, double h)
{
  return h * function_E (S, E + h / 2 * function_E (S, E, I, N), I, N);
}

double
function_I (double E, double I)
{
  return k * E - B * I - mu * I;
}

double
delta_I (double E, double I, double h)
{
  return h * function_I (E, I + h / 2 * function_I (E, I));
}

double
function_R (double E, double I, double R)
{
  return B * I + p * E - y * R;
}

double
delta_R (double E, double I, double R, double h)
{
  return h * function_R (E, I, R + h / 2 * function_R (E, I, R));
}

double
function_D (double I)
{
  return mu * I;
}

int
main ()
{
  FILE *out;
  out = fopen ("data.txt", "w");
  double t0 = 0, T = 90, h = 1;
  int n = (T - t0) / h;
  n++;
  double S[n], E[n], I[n], R[n], D[n], N[n];
  double t[n];
  E[0] = 99;
  R[0] = 24;
  S[0] = 2798170 - E[0] - R[0];
  I[0] = 0;
  D[0] = 0;
  N[0] = E[0] + R[0] + S[0] + I[0] + D[0];
  t[0] = t0;
  for (int i = 1; i < n; i++)
    {
      t[i] = t0 + i * h;
      S[i] = S[i - 1]
             + delta_S (S[i - 1], E[i - 1], I[i - 1], R[i - 1], N[i - 1], h);
      E[i] = E[i - 1] + delta_E (S[i - 1], E[i - 1], I[i - 1], N[i - 1], h);
      I[i] = I[i - 1] + delta_I (E[i - 1], I[i - 1], h);
      R[i] = R[i - 1] + delta_R (E[i - 1], I[i - 1], R[i - 1], h);
      D[i] = D[i - 1] + function_D (I[i - 1]);
      N[i] = S[i] + E[i] + I[i] + R[i] + D[i];
    }
  for (int i = 0; i < n; i++)
    {
      fprintf (out, "%.1f %.2f %.2f %.2f %.2f %.2f %.2f\n", t[i], N[i], S[i],
               E[i], I[i], R[i], D[i]);
    }

  fclose (out);
  return 0;
}