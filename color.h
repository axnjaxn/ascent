#ifndef _BPJ_ASCENT_COLOR_H
#define _BPJ_ASCENT_COLOR_H

#include <cstdint>

//In this file, YUV will be synonymous with YCbCr

union YUVA_Color {
  struct {uint8_t Y, U, V, A;};
  uint32_t YUVA;
};

union RGBA_Color {
  struct {uint8_t R, G, B, A;};
  uint32_t RGBA;
};

YUVA_Color toYUVA(RGBA_Color rgba);
RGBA_Color toRGBA(YUVA_Color yuva);

#endif
