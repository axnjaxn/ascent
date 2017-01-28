#ifndef _BPJ_ASCENT_GENOME_H
#define _BPJ_ASCENT_GENOME_H

#include "poly.h"

class Genome {
public:
  std::vector<Poly> polys;

  Genome() { }

  void lengthen(double p);
  void mutate(double p, double sigma_c, double sigma_v);
  static Genome crossover(const Genome& g1, const Genome& g2, double p);
};


#endif
