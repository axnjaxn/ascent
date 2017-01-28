#include "population.h"

#include <limits>

#include <cmath>

Population::Population(Evaluator* eval, int N, int K, int maxpop) : eval(eval), N(N), K(K), maxpop(maxpop) {
  pop.assign(maxpop, {Genome(N, K), std::numeric_limits<float>::lowest()});
}

Population Population::random(Evaluator* eval, int N, int K, int maxpop) {
  Population P(eval, N, K, maxpop);
  Genome genome;
  
  for (int i = 0; i < P.pop.size(); i++) {
    genome = Genome::random(N, K);
    P.pop[i] = {genome, eval->evaluate(P.pop[i].genome)};
  }
  P.sortByQuality();

  return P;
}

void Population::sortByQuality() {
  //TODO
}

void Population::cull() {
  pop.resize((int)ceil(elite * pop.size()));
}

Genome Population::makeChild() const {
  return Genome(N, K);//TODO
}

void Population::repopulate() {
  std::vector<CachedGenome> next = pop;
  Genome genome;
  
  while (next.size() < maxpop) {
    genome = makeChild();
    next.push_back({genome, eval->evaluate(genome)});
  }

  pop = next;
  sortByQuality();
}

void Population::advance() {
  cull();
  repopulate();
}
