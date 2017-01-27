#include "gray.h"

template <> GrayByte toGrayCode(uint8_t v) {
  return v;//TODO
}

template <> GrayShort toGrayCode(uint16_t v) {
  return v;//TODO
}

template <> GrayInt toGrayCode(uint32_t v) {
  return v;//TODO
}

template <> uint8_t fromGrayCode(GrayByte v) {
  return v;//TODO
}

template <> uint16_t fromGrayCode(GrayShort v) {
  return v;//TODO
}

template <> uint32_t fromGrayCode(GrayInt v) {
  return v;//TODO
}
