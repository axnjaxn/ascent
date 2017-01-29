#include "genome.h"
#include "random.h"

#include <cstdlib>

void wobbleByte(uint8_t& v, double sigma) {
  v = (uint8_t)(v + Random::gaussian(sigma));
}

void wobbleScalar(float& f, double sigma) {
  f = (float)(f + Random::gaussian(sigma));
  f = (f < 0.0f)? 0.0f : (f > 1.0f)? 1.0f : f;
}

void Genome::mutate(double sigma_c, double sigma_v) {
  int ind = Random::randomInt(polys.size() + 1);

  if (!ind) {
    //Add polygon in random position
    ind = Random::randomInt(polys.size() + 1);

    auto poly = makePoly(3);
    poly.color.YUVA = Random::randomInt();
    for (auto& v : poly.verts)
      v = {(float)Random::uniform(), (float)Random::uniform()};
    
    polys.insert(polys.begin() + ind, poly);
  }
  else {
    auto& poly = polys[ind - 1];
    ind = Random::randomInt(poly.verts.size() + 5);
    
    if (ind < 4) {
      if (ind == 0) wobbleByte(poly.color.Y, sigma_c);
      else if (ind == 1) wobbleByte(poly.color.U, sigma_c);
      else if (ind == 2) wobbleByte(poly.color.V, sigma_c);
      else wobbleByte(poly.color.A, sigma_c);
    }
    else {
      ind -= 4;
      
      if (ind == poly.verts.size())
	poly.verts.push_back({(float)Random::uniform(), (float)Random::uniform()});
      else {
	auto& v = poly.verts[ind];
	wobbleScalar(v.x, sigma_v);
	wobbleScalar(v.y, sigma_v);
      }
      
      normalize(poly);
    }
  }
}
