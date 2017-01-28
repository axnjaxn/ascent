#ifndef _BPJ_ASCENT_COLOR_H
#define _BPJ_ASCENT_COLOR_H

#include "gray.h"

//In this file, YUV will be synonymous with YCbCr

union Color {
  struct {GrayByte Y, U, V, A;};
  uint32_t YUVA;
};

union YUVA_Color {
  struct {uint8_t Y, U, V, A;};
  uint32_t YUVA;
};

union RGBA_Color {
  struct {uint8_t R, G, B, A;};
  uint32_t RGBA;
};

Color toColor(YUVA_Color yuva);
Color toColor(RGBA_Color rgba);

YUVA_Color toYUVA(Color color);
YUVA_Color toYUVA(RGBA_Color rgba);

RGBA_Color toRGBA(Color color);
RGBA_Color toRGBA(YUVA_Color yuva);

#endif
