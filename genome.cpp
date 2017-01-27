#include "genome.h"

Genome::Genome(int N, int K) {
  polys.assign(N, makePoly(K));
}

Genome Genome::random(int N, int K) {
  Genome genome(N, K);

  //TODO: Initialize values
  
  return genome;
}

void Genome::mutate(double p) {
  //TODO
}

void Genome::crossover(Genome& g1, Genome& g2, double p) {
  //TODO
}

void Genome::normalize() {
  //TODO
}
