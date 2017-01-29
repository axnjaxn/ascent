#ifndef _BPJ_ASCENT_RANDOM_H
#define _BPJ_ASCENT_RANDOM_H

#include <cstdint>

namespace Random {
  void resetDefault();
  void seedTime();
  uint8_t randomByte();
  uint32_t randomInt();
  unsigned int randomInt(unsigned int n);
  double uniform();
  double gaussian(double stdev);
  bool choice(double p); 
}

#endif
