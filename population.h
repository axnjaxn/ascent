#ifndef _BPJ_GENOME_POPULATION_H
#define _BPJ_GENOME_POPULATION_H

#include "genome.h"

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
  
  int N, K;
  std::vector<CachedGenome> pop;

  int maxpop;
  float elite = 0.1;
  double pmutate = 0.01, pcrossover = 0.5;

  Population(Evaluator* eval, int N, int K, int maxpop);
  static Population random(Evaluator* eval, int N, int K, int maxpop);

  void sortByQuality();
  void cull();
  Genome makeChild() const;
  void repopulate();

  void advance();
};

#endif
