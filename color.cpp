#include "color.h"

inline uint8_t clampByte(float f) {return (f < 0)? 0 : (f > 255)? 255 : (uint8_t)(f + 0.5f);}

Color toColor(YUVA_Color yuva) {
  Color color;
  
  color.Y = toGrayCode(yuva.Y);
  color.U = toGrayCode(yuva.U);
  color.V = toGrayCode(yuva.V);
  color.A = toGrayCode(yuva.A);

  return color;
}

Color toColor(RGBA_Color rgba) {
  return toColor(toYUVA(rgba));
}

YUVA_Color toYUVA(Color color) {
  YUVA_Color yuva;
  
  yuva.Y = fromGrayCode(color.Y);
  yuva.U = fromGrayCode(color.U);
  yuva.V = fromGrayCode(color.V);
  yuva.A = fromGrayCode(color.A);

  return yuva;
}

YUVA_Color toYUVA(RGBA_Color rgba) {
  YUVA_Color yuva;  
  float r = fromGrayCode(rgba.R), g = fromGrayCode(rgba.G), b = fromGrayCode(rgba.B);

  yuva.Y = clampByte(0.299f * r + 0.587f * g + 0.114f * b);
  yuva.U = clampByte(0.564f * (b - yuva.Y) + 128.0f);
  yuva.V = clampByte(0.713f * (r - yuva.Y) + 128.0f);  
  yuva.A = rgba.A;

  return yuva;
}

RGBA_Color toRGBA(Color color) {
  return toRGBA(toYUVA(color));
}

RGBA_Color toRGBA(YUVA_Color yuva) {
  RGBA_Color rgba;

  rgba.R = clampByte(yuva.Y + 1.403f * (yuva.V - 128.0f));
  rgba.G = clampByte(yuva.Y - 0.714f * (yuva.V - 128.0f) - 0.344 * (yuva.U - 128.0f));
  rgba.B = clampByte(yuva.Y + 1.773f * (yuva.U - 128.0f));
  rgba.A = yuva.A;

  return rgba;
}
