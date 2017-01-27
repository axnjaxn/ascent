#include "gray.h"

template <> GrayByte toGrayCode(uint8_t v) {
  return v ^ (v >> 1);
}

template <> GrayShort toGrayCode(uint16_t v) {
  return v ^ (v >> 1);
}

template <> GrayInt toGrayCode(uint32_t v) {
  return v ^ (v >> 1);
}

template <> uint8_t fromGrayCode(GrayByte v) {
  v = v ^ (v >> 4);
  v = v ^ (v >> 2);
  v = v ^ (v >> 1);
  return v;
}

template <> uint16_t fromGrayCode(GrayShort v) {
  v = v ^ (v >> 8);
  v = v ^ (v >> 4);
  v = v ^ (v >> 2);
  v = v ^ (v >> 1);
  return v;

}

template <> uint32_t fromGrayCode(GrayInt v) {
  v = v ^ (v >> 16);
  v = v ^ (v >> 8);
  v = v ^ (v >> 4);
  v = v ^ (v >> 2);
  v = v ^ (v >> 1);
  return v;

}
