#ifndef _BPJ_GENOME_POPULATION_H
#define _BPJ_GENOME_POPULATION_H

#include "genome.h"

#include <functional>

using CachedGenome = struct _CachedGenome {
  Genome genome;
  double quality;
};

class Evaluator {
public:
  virtual double evaluate(const Genome& genome) = 0;
};

class Population {
public:
  int generation;
  
  Evaluator* eval;
  
  std::vector<CachedGenome> pop;

  int maxpop;
  float elite = 0.3;
  double plengthen = 0.05, pmutate = 0.01, pcrossover = 0.5;
  double sigma_c = 24.0, sigma_v = 0.2;

  Population(Evaluator* eval, int maxpop);
  void seed(int N, int iterations, std::function<void(int, int, const Genome&, double)> callback);
  
  void sortByQuality();
  void cull();
  Genome makeChild() const;
  void repopulate();

  void advance();

  inline const Genome& best() const {return pop[0].genome;}
  inline const double quality() const {return pop[0].quality;}
};

#endif
