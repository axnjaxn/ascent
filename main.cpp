#include "genome.h"
#include "random.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <byteimage/byteimage.h>

using byteimage::ByteImage;

class Evaluator {
public:
  virtual double evaluate(const Genome&) = 0;
};

class SSIMEvaluator : public Evaluator {
protected:
  ByteImage img;
  std::function<ByteImage(const Genome&)> draw_func;

public:
  SSIMEvaluator(const ByteImage& img, std::function<ByteImage(const Genome&)> draw_func) : img(img), draw_func(draw_func) { }

  double evaluate(const Genome& genome) {
    const int k = 16;
    
    ByteImage raster = draw_func(genome);

    auto sq = [](double x) -> double {return x * x;};
    
    double sum = 0.0, src, dst;
    double msrc, mdst, ssrc, sdst, cov;
    int w, h, N = 0;
    const double c1 = sq(0.01 * 255);
    const double c2 = sq(0.03 * 255);
    for (int ch = 0; ch < 3; ch++)
      for (int y = 0; y < img.nr; y += k) {
	h = std::min(img.nr - y, k);
	for (int x = 0; x < img.nc; x += k) {
	  w = std::min(img.nc - x, k);

	  msrc = mdst = 0.0;
	  for (int r = 0; r < h; r++)
	    for (int c = 0; c < w; c++) {
	      msrc += img.at(y + r, x + c, ch);
	      mdst += raster.at(y + r, x + c, ch);
	    }
	  msrc /= w * h;
	  mdst /= w * h;

	  ssrc = sdst = cov = 0.0;
	  for (int r = 0; r < h; r++)
	    for (int c = 0; c < w; c++) {
	      src = img.at(y + r, x + c, ch) - msrc;
	      dst = raster.at(y + r, x + c, ch) - mdst;

	      ssrc += sq(src);
	      sdst += sq(dst);
	      cov += src * dst;
	    }
	  ssrc /= w * h;
	  sdst /= w * h;
	  cov /= w * h;

	  sum += (2.0 * msrc * mdst + c1) * (2.0 * cov + c2) / ((sq(msrc) + sq(mdst) + c1) * (ssrc + sdst + c2));
	  N++;
	}
      }

    return sum /= N;
  }
};

ByteImage rasterize(SDL_Renderer* render, SDL_Texture* texture, const Genome& genome) {
  SDL_SetRenderTarget(render, texture);

  int nr, nc;
  SDL_QueryTexture(texture, nullptr, nullptr, &nc, &nr);
    
  SDL_SetRenderDrawColor(render, 0, 0, 0, 0xFF);
  SDL_RenderSetLogicalSize(render, nc, nr);
  SDL_RenderClear(render);

  std::vector<int16_t> x, y;
  for (auto poly : genome.polys) {
    x.resize(poly.verts.size());
    y.resize(poly.verts.size());

    for (int i = 0; i < poly.verts.size(); i++) {
      x[i] = (int16_t)(poly.verts[i].x * nc + 0.5f);
      y[i] = (int16_t)(poly.verts[i].y * nr + 0.5f);
    }

    filledPolygonRGBA(render, x.data(), y.data(), x.size(), poly.color.Y, poly.color.U, poly.color.V, poly.color.A);
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

  RGBA_Color color;
  std::vector<int16_t> x, y;
  for (auto& poly : genome.polys) {
    color = toRGBA(poly.color);
    
    x.resize(poly.verts.size());
    y.resize(poly.verts.size());

    for (int i = 0; i < poly.verts.size(); i++) {
      x[i] = (int16_t)(poly.verts[i].x * nc + 0.5f);
      y[i] = (int16_t)(poly.verts[i].y * nr + 0.5f);
    }
    
    filledPolygonRGBA(render, x.data(), y.data(), x.size(), color.R, color.G, color.B, color.A);	
  }
}

ByteImage toYUV(const ByteImage& img) {
  ByteImage yuv(img.nr, img.nc, 3);

  RGBA_Color rgba;
  YUVA_Color yuva;
  for (int r = 0; r < img.nr; r++)
    for (int c = 0; c < img.nc; c++) {
      rgba.R = img.at(r, c, 0);
      rgba.G = img.at(r, c, 1);
      rgba.B = img.at(r, c, 2);
      rgba.A = 0xFF;
      
      yuva = toYUVA(rgba);
      
      yuv.at(r, c, 0) = yuva.Y;
      yuv.at(r, c, 1) = yuva.U;
      yuv.at(r, c, 2) = yuva.V;
    }

  return yuv;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Syntax: %s [image]\n", argv[0]);
    return 0;
  }
  
  ByteImage img(argv[1]);
  ByteImage yuv = toYUV(img);
  
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
    
  SSIMEvaluator eval(yuv, [=](const Genome& genome) -> ByteImage {return rasterize(render, texture, genome);});
  
  Random::seedTime();

  int generation = 0;
  Genome best, next;
  double best_quality = eval.evaluate(best), quality;

  SDL_Event event;
  bool exitflag = false;
  while (!exitflag) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) exitflag = true;
      else if (event.type == SDL_KEYDOWN) {
	if (event.key.keysym.sym == SDLK_F2) {
	  //TODO: Save
	}
	else if (event.key.keysym.sym == SDLK_F3) {
	  //TODO: Load
	}
      }
    }

    ++generation;
    next = best;
    next.mutate(16.0, 0.25);
    quality = eval.evaluate(next);
    if (quality > best_quality) {
      best = next;
      best_quality = quality;

      draw(render, best);
      SDL_RenderPresent(render);
      
      printf("\rGeneration %d: Quality %lf\n", generation, best_quality);
      fflush(stdout);
    }
  }
  
  return 0;
}
