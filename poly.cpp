#include "poly.h"

#include <cmath>

Poly makePoly(int K) {
  Poly poly;

  poly.color.YUVA = 0;
  poly.verts.resize(K, {0.0, 0.0});

  return poly;
}

float ccw(const Vert& p1, const Vert& p2, const Vert& p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

void normalize(Poly& poly) {
  int N = poly.verts.size();
  
  for (int i = 1; i < N; i++)
    if (poly.verts[i].y < poly.verts[0].y
	|| (poly.verts[i].y == poly.verts[0].y && poly.verts[i].x < poly.verts[0].x)) 
      std::swap(poly.verts[0], poly.verts[i]);

  double best_angle, angle;
  for (int i = 1; i < N - 1; i++) {
    best_angle = atan2(poly.verts[i].y - poly.verts[0].y, poly.verts[i].x - poly.verts[0].x); 
    for (int j = i + 1; j < N; j++) {
      angle = atan2(poly.verts[j].y - poly.verts[0].y, poly.verts[j].x - poly.verts[0].x); 
      if (angle < best_angle) {
	std::swap(poly.verts[i], poly.verts[j]);
	best_angle = angle;
      }
    }
  }
  
  poly.verts.push_back(poly.verts[0]);

  int M = 1;
  for (int i = 2; i <= N; i++) {
    while (ccw(poly.verts[M - 1], poly.verts[M], poly.verts[i]) <= 0)
      if (M > 1) M--;
      else if (i == N) break;
      else i++;
  
    M++;
    std::swap(poly.verts[i], poly.verts[M]);
  }

  poly.verts.resize(M);
}
