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

void Direct(const SpatialImage& input, FrequencyImage& output);

void Separable(const SpatialImage& input, FrequencyImage& output);

void Fast(const SpatialImage& input, FrequencyImage& output);

} // End of Fourier namespace
} // End of Elba namespace
