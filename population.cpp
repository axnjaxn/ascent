#include "population.h"

#include <algorithm>
#include <limits>

#include <cmath>

Population::Population(Evaluator* eval, int maxpop) : eval(eval), maxpop(maxpop), generation(0) {
  pop.assign(maxpop, {Genome(), std::numeric_limits<float>::lowest()});
}

void Population::seed(int N, int iterations) {
  //TODO: Accelerated mutation
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
  child.mutate(pmutate, sigma_c, sigma_v);
  child.lengthen(plengthen);
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
  generation++;
}
