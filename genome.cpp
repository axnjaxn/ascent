#include "genome.h"
#include "random.h"

#include <cstdlib>

void Genome::lengthen(double p) {
  if (!Random::choice(p)) return;

  int ind = Random::randomInt(polys.size() + 1);

  auto poly = makePoly(3);
  poly.color.YUVA = Random::randomInt();
  for (auto& v : poly.verts)
    v = {(float)Random::uniform(), (float)Random::uniform()};
  
  polys.insert(polys.begin() + ind, poly);
}

void wobbleByte(uint8_t& v, double sigma) {
  v = (uint8_t)(v + Random::gaussian(sigma));
}

void wobbleScalar(float& f, double sigma) {
  f = (float)(f + Random::gaussian(sigma));
  f = (f < 0.0f)? 0.0f : (f > 1.0f)? 1.0f : f;
}

void Genome::mutate(double p, double sigma_c, double sigma_v) {
  bool flag;
  for (auto& poly : polys) {
    flag = false;

    if (Random::choice(p)) wobbleByte(poly.color.Y, sigma_c);
    if (Random::choice(p)) wobbleByte(poly.color.U, sigma_c);
    if (Random::choice(p)) wobbleByte(poly.color.V, sigma_c);
    if (Random::choice(p)) wobbleByte(poly.color.A, sigma_c);

    for (auto& v : poly.verts)
      if (Random::choice(p)) {
	wobbleScalar(v.x, sigma_v);
	wobbleScalar(v.y, sigma_v);
	flag = true;
      }

    if (Random::choice(p)) {
      poly.verts.push_back({(float)Random::uniform(), (float)Random::uniform()});
      flag = true;
    }

    if (flag) normalize(poly);
  }
}

Genome Genome::crossover(const Genome& g1, const Genome& g2, double p) {
  int N = std::max(g1.polys.size(), g2.polys.size());
  
  /*
   * First, create an "alignment array" for each genome
   */
  
  std::vector<unsigned int> a1(g1.polys.size()), a2(g2.polys.size());
  
  for (int i = 0; i < a1.size(); i++) a1[i] = i + 1;
  while (a1.size() < N)
    a1.insert(a1.begin() + Random::randomInt(a1.size() + 1), 0);

  for (int i = 0; i < a2.size(); i++) a2[i] = i + 1;
  while (a2.size() < N)
    a2.insert(a2.begin() + Random::randomInt(a2.size() + 1), 0);
 
  /*
   * Then, use the alignment arrays to establish crossover.
   * If a zero exists in the array, take the opposite gene.
   * Note that this can only happen for one of the two genomes.
   * Also note that this process can, over time, create "Junk DNA!"
   */

  Genome child;
  child.polys.resize(N);
  
  for (int i = 0; i < N; i++)
    if (!a1[i]) child.polys[i] = g2.polys[a2[i] - 1];
    else if (!a2[i] || Random::choice(p)) child.polys[i] = g1.polys[a1[i] - 1];
    else child.polys[i] = g2.polys[a2[i] - 1];

  return child;
}
