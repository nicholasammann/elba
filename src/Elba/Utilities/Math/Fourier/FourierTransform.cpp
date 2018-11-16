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
    }
  }
}

void Separable(const SpatialImage& input, FrequencyImage& output)
{
  FrequencyImage temp;
  size_t colSize = input.size();
  temp.resize(colSize);

  for (int y = 0; y < colSize; ++y)
  {
    size_t rowSize = input[y].size();
    double exp = (2.0 * pi) / static_cast<double>(rowSize);
    temp[y].resize(rowSize);

    for (int v = 0; v < rowSize; ++v)
    {
      temp[y][v] = ComplexNumber(0, 0);

      for (int x = 0; x < rowSize; ++x)
      {
        temp[y][v].real += input[y][x] * cos(exp * x * v);
        temp[y][v].imaginary -= input[y][x] * sin(exp * x * v);
      }
    }
  }

  double exp = (2.0 * pi) / static_cast<double>(input.size());
  output.resize(input.size());
  for (int u = 0; u < input.size(); ++u)
  {
    output[u].resize(input[u].size());
    for (int v = 0; v < input[u].size(); ++v)
    {
      output[u][v] = ComplexNumber(0, 0);
      
      for (int x = 0; x < input[u].size(); ++x)
      {
        output[u][v].real = (cos(exp * x * y) * temp[y][x].real - sin(exp * x * y) * temp[y][x].imaginary);
        output[u][v].imaginary = (cos(exp * x * y) * temp[y][x].imaginary + temp[y][x].real * -sin(exp * x * y));
      }
    }
  }
}

void Fast(const SpatialImage& input, FrequencyImage& output)
{

}
} // End of Fourier namespace
} // End of Elba namespace
