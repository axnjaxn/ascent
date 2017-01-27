#ifndef _BPJ_ASCENT_POLY_H
#define _BPJ_ASCENT_POLY_H

#include "color.h"

#include <vector>

using Vert = union {
  struct {GrayShort X, Y;};
  uint32_t XY;
};

using FloatVert = struct {
  float x, y;
};

Vert noVert();
bool isVert(Vert v);
FloatVert toFloat(Vert v, int width, int height);

using Poly = struct {
  Color color;
  std::vector<Vert> verts;
};

Poly makePoly(int K);

#endif
