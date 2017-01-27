#ifndef _BPJ_ASCENT_GENOME_H
#define _BPJ_ASCENT_GENOME_H

#include "poly.h"

class Genome {
public:
  std::vector<Poly> polys;

  Genome(int N, int K);
  static Genome random(int N, int K);
  
  void mutate(double p);
  static void crossover(Genome& g1, Genome& g2, double p);
  void normalize();
};


#endif
