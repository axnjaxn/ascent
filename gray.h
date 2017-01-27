#ifndef _BPJ_ASCENT_GRAY_H
#define _BPJ_ASCENT_GRAY_H

#include <cstdint>

using GrayByte = uint8_t;
using GrayShort = uint16_t;
using GrayInt = uint32_t;

template <typename tn>
tn toGrayCode(tn t);

template <typename tn>
tn fromGrayCode(tn t);

#endif
