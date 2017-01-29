#ifndef _BPJ_ASCENT_GENOME_H
#define _BPJ_ASCENT_GENOME_H

#include "poly.h"

class Genome {
public:
  std::vector<Poly> polys;

  Genome() { }

  void mutate(double sigma_c, double sigma_v);
};

#endif
