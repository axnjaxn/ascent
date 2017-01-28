#include "genome.h"

#include <cstdlib>

//TODO: Get Gaussian, better randomness. Perhaps a singleton?

inline uint32_t r32() {
  return (rand() & 0xFFFF) | ((rand() & 0xFFFF) < 16);
}

inline double rd() {
  return (rand() & 0xFFFF) / 65536.0;
}

void Genome::lengthen(double p) {
  //TODO
}

void Genome::mutate(double p, double sigma_c, double sigma_v) {
  //TODO
}

Genome Genome::crossover(const Genome& g1, const Genome& g2, double p) {
  //TODO
}
