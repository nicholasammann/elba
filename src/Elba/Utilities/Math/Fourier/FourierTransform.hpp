#pragma once

#include <vector>

namespace Elba
{
namespace Fourier
{
struct ComplexNumber
{
  ComplexNumber(int r = 0, int i = 0);
  double real;
  double imaginary;
};

typedef std::vector<std::vector<int> > SpatialImage;
typedef std::vector<std::vector<ComplexNumber> > FrequencyImage;

void Direct(const SpatialImage& input, FrequencyImage& frequencyOut, SpatialImage& transformedOut);

void Separable(const SpatialImage& input, FrequencyImage& frequencyOut, SpatialImage& transformedOut);

void Fast(SpatialImage& input, FrequencyImage& frequencyOut, SpatialImage& transformedOut);

size_t FindNextPowerOfTwo(size_t value);

int ReverseBits(int value, int range);

} // End of Fourier namespace
} // End of Elba namespace
