#include "aco.h"
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

ACO::ACO (int nAnts, int nCities, double alpha, double beta, double q,
          double ro, double taumax, int initCity)
{
  NumberOfAnts = nAnts;
  NumberOfCities = nCities;
  ALPHA = alpha;
  BETA = beta;
  Q = q;
  RO = ro;
  TAUMAX = taumax;
  InitialCity = initCity;

  randoms = new Randoms (21);
}

ACO::~ACO ()
{
  for (int i = 0; i < NumberOfCities; i++)
    {
      delete[] Graph[i];
      delete[] Cities[i];
      delete[] Pheromones[i];
      delete[] DeltaPheromones[i];
      if (i < NumberOfCities - 1)
        {
          delete[] Probs[i];
        }
    }
  delete[] Graph;
  delete[] Cities;
  delete[] Pheromones;
  delete[] DeltaPheromones;
  delete[] Probs;
}

void
ACO::init ()
{
  Graph = new int *[NumberOfCities];
  Cities = new double *[NumberOfCities];
  Pheromones = new double *[NumberOfCities];
  DeltaPheromones = new double *[NumberOfCities];
  Probs = new double *[NumberOfCities - 1];
  for (int i = 0; i < NumberOfCities; i++)
    {
      Graph[i] = new int[NumberOfCities];
      Cities[i] = new double[2];
      Pheromones[i] = new double[NumberOfCities];
      DeltaPheromones[i] = new double[NumberOfCities];
      Probs[i] = new double[2];

      for (int j = 0; j < 2; j++)
        {
          Cities[i][j] = -1.0;
          Probs[i][j] = -1.0;
        }
      for (int j = 0; j < NumberOfCities; j++)
        {
          Graph[i][j] = 0;
          Pheromones[i][j] = 0.0;
          DeltaPheromones[i][j] = 0.0;
        }
    }

  Routes = new int *[NumberOfAnts];

  for (int i = 0; i < NumberOfAnts; i++)
    {
      Routes[i] = new int[NumberOfCities];
      for (int j = 0; j < NumberOfCities; j++)
        {
          Routes[i][j] = -1;
        }
    }

  BestLenght = (double)INT_MAX;
  BestRoute = new int[NumberOfCities];
  for (int i = 0; i < NumberOfCities; i++)
    {
      BestRoute[i] = -1;
    }
}

void
ACO::connectCities (int cityi, int cityj)
{
  Graph[cityi][cityj] = 1;
  Pheromones[cityi][cityj] = randoms->Uniforme () * TAUMAX;
  Graph[cityj][cityi] = 1;
  Pheromones[cityj][cityi] = Pheromones[cityi][cityj];
}

void
ACO::setCityPos (int city, double x, double y)
{
  Cities[city][0] = x;
  Cities[city][1] = y;
}

void
ACO::printPheromones ()
{
  cout << "Pheromones: " << endl;
  cout << " | ";
  for (int i = 0; i < NumberOfCities; i++)
    {
      printf ("%5d   ", i);
    }
  cout << endl << "- | ";
  for (int i = 0; i < NumberOfCities; i++)
    {
      cout << "-------";
    }
  cout << endl;
  for (int i = 0; i < NumberOfCities; i++)
    {
      cout << i << " | ";
      for (int j = 0; j < NumberOfCities; j++)
        {
          if (i == j)
            {
              printf ("%5s    ", "x");
              continue;
            }
          if (exists (i, j))
            {
              printf ("%7.3f ", Pheromones[i][j]);
            }
          else
            {
              if (Pheromones[i][j] == 0.0)
                {
                  printf ("%5.0f   ", Pheromones[i][j]);
                }
              else
                {
                  printf ("%7.3f ", Pheromones[i][j]);
                }
            }
        }
      cout << endl;
    }
  cout << endl;
}

double
ACO::dist (int cityi, int cityj)
{
  return (double)sqrt (pow (Cities[cityi][0] - Cities[cityj][0], 2)
                       + pow (Cities[cityi][1] - Cities[cityj][1], 2));
}

bool
ACO::exists (int cityi, int cityj)
{
  return (Graph[cityi][cityj] == 1);
}

bool
ACO::visited (int antk, int c)
{
  for (int l = 0; l < NumberOfCities; l++)
    {
      if (Routes[antk][l] == -1)
        {
          break;
        }
      if (Routes[antk][l] == c)
        return true;
    }
  return false;
}

double
ACO::PHI (int cityi, int cityj, int antk)
{
  double ETAij = (double)pow (1 / dist (cityi, cityj), BETA);
  double TAUij = (double)pow (Pheromones[cityi][cityj], ALPHA);

  double sum = 0.0;

  for (int c = 0; c < NumberOfCities; c++)
    {
      if (exists (cityi, c))
        {
          if (!visited (antk, c))
            {
              double ETA = (double)pow (1 / dist (cityi, c), BETA);
              double TAU = (double)pow (Pheromones[cityi][c], ALPHA);
              sum += ETA * TAU;
            }
        }
    }
  return (ETAij * TAUij) / sum;
}

double
ACO::length (int antk)
{
  double sum = 0.0;
  for (int j = 0; j < NumberOfCities - 1; j++)
    {
      sum += dist (Routes[antk][j], Routes[antk][j + 1]);
    }
  return sum;
}

int
ACO::city ()
{
  double xi = randoms->Uniforme ();
  int i = 0;
  double sum = Probs[i][0];
  while (sum < xi)
    {
      i++;
      sum += Probs[i][0];
    }
  return (int)Probs[i][1];
}

void
ACO::route (int antk)
{
  Routes[antk][0] = InitialCity;
  for (int i = 0; i < NumberOfCities - 1; i++)
    {
      int cityi = Routes[antk][i];
      int count = 0;
      for (int c = 0; c < NumberOfCities; c++)
        {
          if (cityi == c)
            {
              continue;
            }
          if (exists (cityi, c))
            {
              if (!visited (antk, c))
                {
                  Probs[count][0] = PHI (cityi, c, antk);
                  Probs[count][1] = (double)c;
                  count++;
                }
            }
        }
      if (count == 0)
        {
          return;
        }

      Routes[antk][i + 1] = city ();
    }
}

int
ACO::valid (int antk, int iteration)
{
  for (int i = 0; i < NumberOfCities - 1; i++)
    {
      int cityi = Routes[antk][i];
      int cityj = Routes[antk][i + 1];
      if (cityi < 0 || cityj < 0)
        {
          return -1;
        }
      if (!exists (cityi, cityj))
        {
          return -2;
        }
      for (int j = 0; j < i - 1; j++)
        {
          if (Routes[antk][i] == Routes[antk][j])
            {
              return -3;
            }
        }
    }

  if (!exists (InitialCity, Routes[antk][NumberOfCities - 1]))
    {
      return -4;
    }

  return 0;
}

void
ACO::printGraph ()
{
  cout << "Graph: " << endl;
  cout << " | ";

  for (int i = 0; i < NumberOfCities; i++)
    {
      cout << i << " ";
    }
  cout << endl << "- | ";
  for (int i = 0; i < NumberOfCities; i++)
    {
      cout << "- ";
    }
  cout << endl;
  int count = 0;
  for (int i = 0; i < NumberOfCities; i++)
    {
      cout << i << " | ";
      for (int j = 0; j < NumberOfCities; j++)
        {
          if (i == j)
            {
              cout << "x ";
            }
          else
            {
              cout << Graph[i][j] << " ";
            }
          if (Graph[i][j] == 1)
            {
              count++;
            }
        }
      cout << endl;
    }
  cout << endl;
  cout << "Number of connections: " << count << endl << endl;
}

void
ACO::printResult ()
{
  BestLenght += dist (BestRoute[NumberOfCities - 1], InitialCity);
  cout << "Best Route: " << endl;
  for (int i = 0; i < NumberOfCities; i++)
    {
      cout << BestRoute[i] << " ";
    }
  cout << endl << "length: " << BestLenght << endl;
  cout << endl << "Ideal Route: " << endl;
  cout << "0 7 6 2 4 5 1 3" << endl;
  cout << "lenght: 127.509" << endl;
}

void
ACO::updatePheromones ()
{
  for (int k = 0; k < NumberOfAnts; k++)
    {
      double rlenght = length (k);
      for (int r = 0; r < NumberOfCities - 1; r++)
        {
          int cityi = Routes[k][r];
          int cityj = Routes[k][r + 1];
          DeltaPheromones[cityi][cityj] += Q / rlenght;
          DeltaPheromones[cityj][cityi] += Q / rlenght;
        }
    }
  for (int i = 0; i < NumberOfCities; i++)
    {
      for (int j = 0; j < NumberOfCities; j++)
        {
          Pheromones[i][j]
              = (1 - RO) * Pheromones[i][j] + DeltaPheromones[i][j];
          DeltaPheromones[i][j] = 0.0;
        }
    }
}

void
ACO::optimize (int ITERATIONS)
{
  for (int iterations = 1; iterations <= ITERATIONS; iterations++)
    {
      cout << flush;
      cout << "ITERATION " << iterations << "HAS STARTED" << endl << endl;

      for (int k = 0; k < NumberOfAnts; k++)
        {
          cout << " : ant " << k << "has been released" << endl;
          while (0 != valid (k, iterations))
            {
              cout << " :: releasing ant " << k << "again" << endl;
              for (int i = 0; i < NumberOfCities; i++)
                {
                  Routes[k][i] = -1;
                }
              route (k);
            }

          for (int i = 0; i < NumberOfCities; i++)
            {
              cout << Routes[k][i] << " ";
            }
          cout << endl;

          cout << "  :: route done" << endl;
          double rlenght = length (k);

          if (rlenght < BestLenght)
            {
              BestLenght = rlenght;
              for (int i = 0; i < NumberOfCities; i++)
                {
                  BestRoute[i] = Routes[k][i];
                }
            }
          cout << ": ant " << k << "has ended" << endl;
        }

      cout << endl << "updating Pheromones . . .";
      updatePheromones ();
      cout << " done! " << endl << endl;
      printPheromones ();

      for (int i = 0; i < NumberOfAnts; i++)
        {
          for (int j = 0; j < NumberOfCities; j++)
            {
              Routes[i][j] = -1;
            }
        }
      cout << endl
           << "iteration " << iterations << "has ended" << endl
           << endl;
    }
}
