#include "population.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <byteimage/byteimage.h>

using byteimage::ByteImage;

class ImageEvaluator : public Evaluator {
protected:
  ByteImage img;
  std::function<ByteImage(const Genome&)> draw_func;

public:  
  ImageEvaluator(const ByteImage& img, std::function<ByteImage(const Genome&)> draw_func) : img(img), draw_func(draw_func) { }

  double evaluate(const Genome& genome) {
    ByteImage raster = draw_func(genome);

    //TODO: Upgrade this to SSIM / change to YUV
    
    double sum = 0.0, v;
    for (int ch = 0; ch < 3; ch++)
      for (int r = 0; r < img.nr; r++)
	for (int c = 0; c < img.nc; c++) {
	  v = byteimage::diff(raster.at(r, c, ch), img.at(r, c, ch)) / 255.0;
	  sum += v * v;
	}
    sum /= img.nr * img.nc * 3;
    
    return 1.0 - sum;
  }
};

ByteImage rasterize(SDL_Renderer* render, SDL_Texture* texture, const Genome& genome) {
  SDL_SetRenderTarget(render, texture);

  int nr, nc;
  SDL_QueryTexture(texture, nullptr, nullptr, &nc, &nr);
    
  SDL_SetRenderDrawColor(render, 0, 0, 0, 0xFF);
  SDL_RenderSetLogicalSize(render, nc, nr);
  SDL_RenderClear(render);

  RGBA_Color rgba;
  std::vector<int16_t> x, y;
  FloatVert fv;
  for (auto poly : genome.polys) {
    rgba.RGBA = toYUVA(poly.color).YUVA;

    x.resize(poly.verts.size());
    y.resize(poly.verts.size());

    for (int i = 0; i < poly.verts.size(); i++) {
      if (isVert(poly.verts[i]))
	fv = toFloat(poly.verts[i], nc, nr);
      else {
	x.resize(i);
	y.resize(i);
	break;
      }
	
      x[i] = (int16_t)(fv.x + 0.5f);
      y[i] = (int16_t)(fv.y + 0.5f);
    }

    if (x.size() < 3) continue;

    filledPolygonRGBA(render, x.data(), y.data(), x.size(), rgba.R, rgba.G, rgba.B, rgba.A);
  }

  uint32_t* px = new uint32_t [nr * nc];
  SDL_RenderReadPixels(render, nullptr, SDL_PIXELFORMAT_RGBA8888, px, nc * 4);

  ByteImage img(nr, nc, 3);
  byteimage::Byte *R = img.R(), *G = img.G(), *B = img.B();
  for (int i = 0; i < nr * nc; i++) {
    R[i] = (px[i] >> 24) & 0xFF;
    G[i] = (px[i] >> 16) & 0xFF;
    B[i] = (px[i] >> 8) & 0xFF;
  }

  delete [] px;
  
  return img;
}

void draw(SDL_Renderer* render, const Genome& genome) {
  SDL_SetRenderTarget(render, nullptr);

  int nr, nc;
  SDL_RenderGetLogicalSize(render, &nc, &nr);

  SDL_SetRenderDrawColor(render, 0, 0, 0, 0xFF);
  SDL_RenderSetLogicalSize(render, nc, nr);
  SDL_RenderClear(render);

  RGBA_Color rgba;
  std::vector<int16_t> x, y;
  FloatVert fv;
  for (auto poly : genome.polys) {
    rgba = toRGBA(poly.color);

    x.resize(poly.verts.size());
    y.resize(poly.verts.size());

    for (int i = 0; i < poly.verts.size(); i++) {
      if (isVert(poly.verts[i]))
	fv = toFloat(poly.verts[i], nc, nr);
      else {
	x.resize(i);
	y.resize(i);
	break;
      }
	
      x[i] = (int16_t)(fv.x + 0.5f);
      y[i] = (int16_t)(fv.y + 0.5f);
    }

    if (x.size() < 3) continue;

    filledPolygonRGBA(render, x.data(), y.data(), x.size(), rgba.R, rgba.G, rgba.B, rgba.A);
  }
}


int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Syntax: %s [image]\n", argv[0]);
    return 0;
  }
  srand(time(NULL));

  ByteImage img(argv[1]);
  
  if (!SDL_WasInit(SDL_INIT_VIDEO)) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      fprintf(stderr, "Error: Could not initialize SDL.\n");
      exit(1);
    }
    
    atexit(SDL_Quit);
  }

  SDL_Window* window = SDL_CreateWindow("Ascent",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					img.nc, img.nr, 0);

  SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
  SDL_RenderSetLogicalSize(render, img.nc, img.nr);

  SDL_Texture* texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, img.nc, img.nr);
    
  ImageEvaluator eval(img, [=](const Genome& genome) -> ByteImage {return rasterize(render, texture, genome);});
  auto pop = Population::random(&eval, 64, 6, 32);

  SDL_Event event;
  bool exitflag = false;
  while (!exitflag) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) exitflag = true;
    }

    pop.advance();
    
    draw(render, pop.pop[0].genome);
    SDL_RenderPresent(render);
  }
  
  return 0;
}
