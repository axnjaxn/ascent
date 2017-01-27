#ifndef _BPJ_ASCENT_COLOR_H
#define _BPJ_ASCENT_COLOR_H

#include "gray.h"

using Color = union {
  struct {GrayByte Y, U, V, A;};
  uint32_t YUVA;
};

using RGBA_Color = union {
  struct {uint8_t R, G, B, A;};
  uint32_t RGBA;
};

RGBA_Color toRGBA(Color color);

#endif
