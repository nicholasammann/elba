#include "Elba/Utilities/Math/Fourier/FourierTransform.hpp"


namespace Elba
{
namespace Fourier
{
const double e = 2.71828;
const double pi = 3.14159;

ComplexNumber::ComplexNumber(int r, int i)
  : real(r)
  , imaginary(i)
{
}

void Direct(const SpatialImage& input, FrequencyImage& output)
{
  double exp = 2.0 * pi;
  output.resize(input.size());

  for (int freqY = 0; freqY < input.size(); ++freqY)
  {
    output[freqY].resize(input[freqY].size());

    for (int freqX = 0; freqX < input[freqY].size(); ++freqX)
    {
      output[freqY][freqX] = ComplexNumber(0, 0);

      for (int spatialY = 0; spatialY < input.size(); spatialY++)
      {
        for (int spatialX = 0; spatialX < input.size(); spatialX++)
        {
          output[freqY][freqX].real += input[spatialY][spatialX] * cos(exp * (freqY * spatialY + freqX * spatialX));
          output[freqY][freqX].imaginary -= input[spatialY][spatialX] * sin(exp * (freqY * spatialY + freqX * spatialX));
        }
      }
    }
  }
}

void Separable(const SpatialImage& input, FrequencyImage& output)
{
  FrequencyImage temp;
  temp.resize(input.size());

  double exp = 0.5 * pi;

  for (int y = 0; y < input.size(); ++y)
  {
    temp.resize(input[y].size());
    for (int x = 0; x < input[y].size(); ++x)
    {
      temp[y][x] = ComplexNumber(0, 0);
      temp[y][x].real += input[y][x] * cos(exp * x * y);
      temp[y][x].imaginary -= input[y][x] * sin(exp * x * y);
    }
  }

  output.resize(input.size());
  for (int y = 0; y < input.size(); ++y)
  {
    output[y].resize(input[y].size());
    for (int x = 0; x < input[y].size(); ++x)
    {
      output[y][x] = ComplexNumber(0, 0);
      output[y][x].real += cos(exp * x * y) * temp[y][x];
      output[y][x].imaginary -= sin(exp * x * y) * temp[y][x];
    }
  }
}
} // End of Fourier namespace
} // End of Elba namespace
