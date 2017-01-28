#ifndef _BPJ_ASCENT_GENOME_H
#define _BPJ_ASCENT_GENOME_H

#include "poly.h"

class Genome {
public:
  std::vector<Poly> polys;

  Genome() { }
  Genome(int N, int K);
  static Genome random(int N, int K);
  
  void mutate(double p);
  static Genome crossover(const Genome& g1, const Genome& g2, double p);
  void normalize();
};


#endif
