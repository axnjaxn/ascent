#include "population.h"

#include <algorithm>
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
  std::sort(pop.begin(), pop.end(),
	    [](const CachedGenome& g1, const CachedGenome& g2) -> bool {return g1.quality > g2.quality;});
}

void Population::cull() {
  pop.resize((int)ceil(elite * pop.size()));
}

Genome Population::makeChild() const {
  Genome child = Genome::crossover(pop[rand() % pop.size()].genome,
				   pop[rand() % pop.size()].genome,
				   pcrossover);
  child.mutate(pmutate);
  return child;
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
