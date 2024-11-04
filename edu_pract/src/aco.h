#include "randoms.cpp"

class ACO
{
public:
  ACO (int nAnts, int nCities, double alpha, double beta, double q, double ro,
       double taumax, int initCity);
  virtual ~ACO ();
  void init ();

  void connectCities (int cityi, int cityj);
  void setCityPos (int city, double x, double y);

  void printPheromones ();
  void printGraph ();
  void printResult ();

  void optimize (int ITERATIONS);

private:
  double dist (int cityi, int cityj);
  bool exists (int cityi, int cityc);
  bool visited (int antk, int c);
  double PHI (int cityi, int cityj, int antk);

  double length (int antk);

  int city ();
  void route (int antk);
  int valid (int antk, int iteration);

  void updatePheromones ();

  int NumberOfAnts, NumberOfCities, InitialCity;
  double ALPHA, BETA, Q, RO, TAUMAX;

  double BestLenght;
  int *BestRoute;

  int **Graph, **Routes;
  double **Cities, **Pheromones, **DeltaPheromones, **Probs;

  Randoms *randoms;
};