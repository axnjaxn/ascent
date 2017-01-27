#include "population.h"

#include <limits>

Population::Population(Evaluator* eval, int N, int K, int maxpop) : eval(eval), N(N), K(K), maxpop(maxpop) {
  CachedGenome cg = {Genome(N, K), std::numeric_limits<float>.lowest()};
  pop.assign(maxpop, cg);
}

Population Population::random(Evaluator* eval, int N, int K, int maxpop) {
  Population P(eval, N, K, maxpop);
  
  for (int i = 0; i < P.pop.size(); i++) {
    P.pop[i].genome = Genome::random(N, K);
    P.pop[i].quality = eval->evaluate(P.pop[i].genome);
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
  CachedGenome cg;
  
  while (next.size() < maxpop) {
    cg.genome = makeChild();
    cg.quality = eval->evaluate(cg.genome());
    next.push_back(cg);
  }

  pop = next;
  sortByQuality();
}

void Population::advance() {
  cull();
  repopulate();
}
