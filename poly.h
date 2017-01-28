#ifndef _BPJ_ASCENT_POLY_H
#define _BPJ_ASCENT_POLY_H

#include "color.h"

#include <vector>

using Vert = struct _Vert {
  float x, y;
};

using Poly = struct _Poly {
  YUVA_Color color;
  std::vector<Vert> verts;
};

Poly makePoly(int K);
void normalize(Poly& poly); //Remove concavity, etc.

#endif
