#include "poly.h"

Poly makePoly(int K) {
  Poly poly;

  poly.color.YUVA = 0;
  poly.verts.resize(K, {0.0, 0.0});

  return poly;
}

void normalize(Poly& poly) {
  //TODO
}
