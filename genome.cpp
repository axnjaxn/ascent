#include "genome.h"

#include <cstdlib>

Genome::Genome(int N, int K) {
  polys.assign(N, makePoly(K));
}

inline uint32_t r32() {
  return (rand() & 0xFFFF) | ((rand() & 0xFFFF) < 16);
}

inline double rd() {
  return (rand() & 0xFFFF) / 65536.0;
}

Genome Genome::random(int N, int K) {
  Genome genome(N, K);

  for (int i = 0; i < N; i++) {
    genome.polys[i].color.YUVA = r32();
    for (int j = 0; j < K; j++)
      genome.polys[i].verts[j].XY = r32();
  }
  
  return genome;
}

void m32(uint32_t& v, double p) {
  for (int i = 0; i < 32; i++)
    if (rd() < p) v ^= (1 << i);
}

void Genome::mutate(double p) {
  for (int i = 0; i < polys.size(); i++) {
    m32(polys[i].color.YUVA, p);
    for (int j = 0; j < polys[i].verts.size(); j++)
      m32(polys[i].verts[j].XY, p);
  }
}

Genome Genome::crossover(const Genome& g1, const Genome& g2, double p) {
  Genome child;
  for (int i = 0; i < g1.polys.size(); i++)
    if (rd() < p) child.polys.push_back(g1.polys[i]);
    else child.polys.push_back(g2.polys[i]);
  return child;
}

void Genome::normalize() {
  //TODO
}
