#include "random.h"

#include <random>

#include <ctime>

std::default_random_engine generator;

void Random::resetDefault() {
  generator.seed(0);
}

void Random::seedTime() {
  generator.seed((int)time(nullptr));
}

uint8_t Random::randomByte() {
  static std::uniform_int_distribution<uint8_t> distribution;
  return distribution(generator);
}

uint32_t Random::randomInt() {
  static std::uniform_int_distribution<uint32_t> distribution;
  return distribution(generator);
}

unsigned int Random::randomInt(unsigned int n) {
  std::uniform_int_distribution<uint32_t> distribution(0, n - 1);
  return distribution(generator);
}

double Random::uniform() {
  static std::uniform_real_distribution<double> distribution;
  return distribution(generator);
}

double Random::gaussian(double stdev) {
  std::normal_distribution<double> distribution(0.0, stdev);
  return distribution(generator);  
}

bool Random::choice(double p) {
  static std::uniform_real_distribution<double> distribution;
  return distribution(generator) < p;
}
