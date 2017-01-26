#include <functional>
#include <vector>

#include <cstdint>

using GrayByte = uint8_t;
using GrayShort = uint16_t;

template <typename tn>
tn toGrayCode(tn t);

template <typename tn>
tn fromGrayCode(tn t);

using Color = union {
  struct {GrayByte Y, U, V, A;};
  uint32_t YUVA;
};

using RGBA_Color = union {
  struct {uint8_t R, G, B, A;};
  uint32_t RGBA;
};

RGBA_Color toRGBA(Color color);

using Vert = union {
  struct {GrayShort X, Y;};
  uint32_t XY;
};

using FloatVert = struct {
  float x, y;
};

bool isVert(Vert v);
FloatVert toFloat(Vert v, int width, int height);

using Poly = struct {
  Color color;
  std::vector<Vert> verts;
};

Poly makePoly(int K);

class Genome {
public:
  std::vector<Poly> polys;

  Genome(int N, int K);
  static Genome random(int N, int K);
  
  void mutate(double p);
  static void crossover(Genome& g1, Genome& g2, double p);
  void normalize();
};

using CachedGenome = struct {
  Genome genome;
  float quality;
};

class Image {
  //TODO
};

class Evaluator {
  virtual float evaluate(const Genome& genome) = 0;
};
//TODO

class Population {
public:
  int generation;
  
  Evaluator* eval;
  
  int N, K;
  std::vector<CachedGenome> pop;

  int maxpop;
  float elite = 0.1;
  double psurvive = 0.0, pmutate = 0.01, pcrossover = 0.5;

  Population(Evaluator* eval, int N, int K, int maxpop);
  static Population random(Evaluator* eval, int N, int K, int maxpop);

  float quality(const Genome& genome) const;
  void sortByQuality();
  void cull();
  Genome makeChild() const;
  void repopulate();

  void advance();
};

int main(int argc, char* argv[]) {
  return 0;
}
