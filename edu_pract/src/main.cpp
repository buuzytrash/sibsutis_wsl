#include "aco.h"
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

#define ITERATIONS (int)5
#define NUMBEROFANTS (int)10
#define NUMBEROFCITIES (int)8

#define ALPHA (double)0.5
#define BETA (double)0.8
#define Q (double)80
#define RO (double)0.2
#define TAUMAX (int)2
#define INITIALCITY (int)0

int
main ()
{
  ACO *ants = new ACO (NUMBEROFANTS, NUMBEROFCITIES, ALPHA, BETA, Q, RO,
                       TAUMAX, INITIALCITY);

  ants->init ();

  ants->connectCities (0, 1);
  ants->connectCities (0, 2);
  ants->connectCities (0, 3);
  ants->connectCities (0, 7);
  ants->connectCities (1, 3);
  ants->connectCities (1, 5);
  ants->connectCities (1, 7);
  ants->connectCities (2, 4);
  ants->connectCities (2, 5);
  ants->connectCities (2, 6);
  ants->connectCities (4, 3);
  ants->connectCities (4, 5);
  ants->connectCities (4, 7);
  ants->connectCities (6, 7);

  ants->setCityPos (0, 1, 1);
  ants->setCityPos (1, 10, 10);
  ants->setCityPos (2, 20, 10);
  ants->setCityPos (3, 10, 30);
  ants->setCityPos (4, 15, 5);
  ants->setCityPos (5, 10, 1);
  ants->setCityPos (6, 20, 20);
  ants->setCityPos (7, 20, 30);

  ants->printGraph ();
  ants->printPheromones ();
  ants->optimize (ITERATIONS);
  ants->printResult ();

  ants->~ACO ();

  return 0;
}