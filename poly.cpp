#include "poly.h"

Vert noVert() {
  Vert v;
  
  v.XY = 0xFFFFFFFF;
  
  return v;
}

bool isVert(Vert v) {return v.XY != 0xFFFFFFFF;}

FloatVert toFloat(Vert v, int width, int height) {
  FloatVert fv;

  fv.x = width * (fromGrayCode(v.X) / 65536.0);
  fv.y = height * (fromGrayCode(v.Y) / 65536.0);

  return fv;
}

Poly makePoly(int K) {
  Poly poly;

  poly.color.YUVA = 0;
  poly.verts.resize(K, noVert());

  return poly;
}
