#include "color.h"

inline uint8_t clampByte(float f) {return (f < 0)? 0 : (f > 255)? 255 : (uint8_t)(f + 0.5f);}

YUVA_Color toYUVA(RGBA_Color rgba) {
  YUVA_Color yuva;

  yuva.Y = clampByte(0.299f * rgba.R + 0.587f * rgba.G + 0.114f * rgba.B);
  yuva.U = clampByte(0.564f * (rgba.B - yuva.Y) + 128.0f);
  yuva.V = clampByte(0.713f * (rgba.R - yuva.Y) + 128.0f);  
  yuva.A = rgba.A;

  return yuva;
}

RGBA_Color toRGBA(YUVA_Color yuva) {
  RGBA_Color rgba;

  rgba.R = clampByte(yuva.Y + 1.403f * (yuva.V - 128.0f));
  rgba.G = clampByte(yuva.Y - 0.714f * (yuva.V - 128.0f) - 0.344 * (yuva.U - 128.0f));
  rgba.B = clampByte(yuva.Y + 1.773f * (yuva.U - 128.0f));
  rgba.A = yuva.A;

  return rgba;
}
