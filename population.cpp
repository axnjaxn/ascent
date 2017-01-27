#include "population.h"

Population::Population(Evaluator* eval, int N, int K, int maxpop) {
  //TODO
}

Population Population::random(Evaluator* eval, int N, int K, int maxpop) {
  //TODO
}

void Population::sortByQuality() {
  //TODO
}

void Population::cull() {
  //TODO
}

Genome Population::makeChild() const {
  return Genome(N, K);//TODO
}

void Population::repopulate() {
  //TODO
}

void Population::advance() {
  //TODO
}
