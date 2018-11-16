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
  int N = input.size();
  output.resize(N);

  // for each element in the frequency domain
  for (int freqY = 0; freqY < N; ++freqY)
  {
    int M = input[freqY].size();
    output[freqY].resize(M);

    for (int freqX = 0; freqX < M; ++freqX)
    {
      output[freqY][freqX] = ComplexNumber(0, 0);

      // for each element in the spatial image
      for (int spatialY = 0; spatialY < N; spatialY++)
      {
        for (int spatialX = 0; spatialX < M; spatialX++)
        {
          double rowTerm = (exp *  static_cast<double>(freqX * spatialX)) / static_cast<double>(M);
          double cosRow = cos(rowTerm);
          double sinRow = -sin(rowTerm);

          double colTerm = (exp * static_cast<double>(freqY * spatialY)) / static_cast<double>(N);
          double cosCol = cos(colTerm);
          double sinCol = -sin(colTerm);

          double term = input[spatialY][spatialX];

          output[freqY][freqX].real += term * (cosRow * cosCol + sinRow * sinCol);
          output[freqY][freqX].imaginary += term * (sinCol * cosRow + sinRow * cosCol);
        }
      }

      output[freqY][freqX].real /= static_cast<double>(N * M);
      output[freqY][freqX].imaginary /= static_cast<double>(N * M);
    }
  }
}

void Separable(const SpatialImage& input, FrequencyImage& output)
{
  FrequencyImage temp;
  size_t colSize = input.size();
  temp.resize(colSize);

  for (int v = 0; v < colSize; ++v)
  {
    size_t rowSize = input[v].size();
    double exp = (2.0 * pi) / static_cast<double>(colSize);
    temp[v].resize(rowSize);

    for (int x = 0; x < rowSize; ++x)
    {
      temp[v][x] = ComplexNumber(0, 0);

      for (int y = 0; y < rowSize; ++y)
      {
        temp[v][x].real += input[y][x] * cos(exp * v * y);
        temp[v][x].imaginary += input[y][x] * -sin(exp * v * y);
      }

      temp[v][x].real /= static_cast<double>(colSize);
      temp[v][x].imaginary /= static_cast<double>(colSize);
    }
  }

  output.resize(colSize);
  for (int v = 0; v < colSize; ++v)
  {
    size_t rowSize = input[v].size();
    double exp = (2.0 * pi) / static_cast<double>(rowSize);
    output[v].resize(rowSize);
    for (int u = 0; u < rowSize; ++u)
    {
      output[v][u] = ComplexNumber(0, 0);
      
      for (int x = 0; x < rowSize; ++x)
      {
        double term = exp * u * x;
        output[v][u].real += (cos(term) * temp[v][x].real - sin(term) * temp[v][x].imaginary);
        output[v][u].imaginary += (cos(term) * temp[v][x].imaginary + temp[v][x].real * -sin(term));
      }

      output[v][u].real /= static_cast<double>(rowSize);
      output[v][u].imaginary /= static_cast<double>(rowSize);
    }
  }
}

void Fast(const SpatialImage& input, FrequencyImage& output)
{

}
} // End of Fourier namespace
} // End of Elba namespace
