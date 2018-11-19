#include <algorithm>

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

void Direct(const SpatialImage& input, FrequencyImage& frequencyOut, SpatialImage& transformedOut)
{
  double exp = 2.0 * pi;
  int N = input.size();
  frequencyOut.resize(N);

  // for each element in the frequency domain
  for (int freqY = 0; freqY < N; ++freqY)
  {
    int M = input[freqY].size();
    frequencyOut[freqY].resize(M);

    for (int freqX = 0; freqX < M; ++freqX)
    {
      frequencyOut[freqY][freqX] = ComplexNumber(0, 0);

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

          frequencyOut[freqY][freqX].real += term * (cosRow * cosCol + sinRow * sinCol);
          frequencyOut[freqY][freqX].imaginary += term * (sinCol * cosRow + sinRow * cosCol);
        }
      }

      frequencyOut[freqY][freqX].real /= static_cast<double>(N * M);
      frequencyOut[freqY][freqX].imaginary /= static_cast<double>(N * M);
    }
  }

  // IDFT
  for (int spatialY = 0; spatialY < N; spatialY++)
  {
    int M = frequencyOut[spatialY].size();
    transformedOut[spatialY].resize(M);

    for (int spatialX = 0; spatialX < M; spatialX++)
    {
      transformedOut[spatialY][spatialX] = 0;

      for (int freqY = 0; freqY < N; ++freqY)
      {
        for (int freqX = 0; freqX < M; ++freqX)
        {
          double rowTerm = (exp *  static_cast<double>(freqX * spatialX)) / static_cast<double>(M);
          double cosRow = cos(rowTerm);
          double sinRow = -sin(rowTerm);

          double colTerm = (exp * static_cast<double>(freqY * spatialY)) / static_cast<double>(N);
          double cosCol = cos(colTerm);
          double sinCol = -sin(colTerm);

          double real = (cosRow * cosCol + sinRow * sinCol);
          double imaginary = (sinCol * cosRow + sinRow * cosCol);
          
          transformedOut[spatialX][spatialY] += real * frequencyOut[freqY][freqX].real - imaginary * frequencyOut[freqY][freqX].imaginary;
        }
      }

      transformedOut[spatialX][spatialY] *= N * M;
    }
  }
}

void Separable(const SpatialImage& input, FrequencyImage& frequencyOut, SpatialImage& transformedOut)
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

  frequencyOut.resize(colSize);
  for (int v = 0; v < colSize; ++v)
  {
    size_t rowSize = input[v].size();
    double exp = (2.0 * pi) / static_cast<double>(rowSize);
    frequencyOut[v].resize(rowSize);
    for (int u = 0; u < rowSize; ++u)
    {
      frequencyOut[v][u] = ComplexNumber(0, 0);
      
      for (int x = 0; x < rowSize; ++x)
      {
        double term = exp * u * x;
        frequencyOut[v][u].real += (cos(term) * temp[v][x].real - sin(term) * temp[v][x].imaginary);
        frequencyOut[v][u].imaginary += (cos(term) * temp[v][x].imaginary + temp[v][x].real * -sin(term));
      }

      frequencyOut[v][u].real /= static_cast<double>(rowSize);
      frequencyOut[v][u].imaginary /= static_cast<double>(rowSize);
    }
  }


  // IDFT
  SpatialImage spatialTemp;
  spatialTemp.resize(colSize);
  for (int y = 0; y < colSize; ++y)
  {
    size_t rowSize = frequencyOut[y].size();
    double exp = (2.0 * pi) / static_cast<double>(colSize);
    spatialTemp[y].resize(rowSize);

    for (int u = 0; u < rowSize; ++u)
    {
      spatialTemp[y][u] = 0;

      for (int v = 0; v < rowSize; ++v)
      {
        double real = cos(exp * v * y);
        double imaginary = -sin(exp * v * y);
        
        spatialTemp[y][u] += frequencyOut[v][u].real * real - frequencyOut[v][u].imaginary * imaginary;
      }

      spatialTemp[y][u] *= colSize;
    }
  }

  /*
  transformedOut.resize(colSize);
  for (int y = 0; y < colSize; ++y)
  {
    size_t rowSize = input[y].size();
    double exp = (2.0 * pi) / static_cast<double>(rowSize);
    transformedOut[y].resize(rowSize);
    for (int x = 0; x < rowSize; ++x)
    {
      transformedOut[y][x] = 0;

      for (int u = 0; u < rowSize; ++u)
      {
        double term = exp * u * x;
        transformedOut[y][x].real += (cos(term) * temp[y][u].real - sin(term) * temp[y][u].imaginary);
        transformedOut[y][x].imaginary += (cos(term) * temp[y][u].imaginary + temp[y][u].real * -sin(term));
      }

      transformedOut[v][u].real /= static_cast<double>(rowSize);
      transformedOut[v][u].imaginary /= static_cast<double>(rowSize);
    }
  }*/
}

void Fast(SpatialImage& input, FrequencyImage& frequencyOut, SpatialImage& transformedOut)
{
  // pad array with 0's to next highest power of 2
  size_t colPadded = Fourier::FindNextPowerOfTwo(input.size());
  input.resize(colPadded);

  for (int j = 0; j < colPadded; j++)
  {
    size_t rowPadded = Fourier::FindNextPowerOfTwo(input[j].size());
    input[j].resize(rowPadded);
  }

  // bit reversal
  for (int j = 0; j < colPadded; j++)
  {
    size_t rowPadded = input[j].size();

    for (int i = 0; i < rowPadded; i++)
    {
      int revIndex = Fourier::ReverseBits(i, rowPadded);

      if (revIndex > i)
      {
        // swap elements
        std::swap(input[j][i], input[j][revIndex]);
      }
    }
  }

  for (int j = 0; j < colPadded; j++)
  {
    size_t rowPadded = input[j].size();
    
    int revIndex = Fourier::ReverseBits(j, rowPadded);

    if (revIndex > j)
    {
      for (int i = 0; i < rowPadded; i++)
      {
        // swap elements
        std::swap(input[j][i], input[revIndex][i]);
      }
    }
  }

  // for each stage of reversed bits (bottom to top)

    // for each box in the stage

      // butterfly calculation (loop through the samples inside any one box)


}

size_t FindNextPowerOfTwo(size_t value)
{
  int count = 0;
  int power = 1;

  while (value > power)
  {
    count++;
    power = power << 1;
  }

  return pow(2, count);
}

int ReverseBits(int value, int range)
{
  int msb = 0;
  int rangeTemp = range;
  while (rangeTemp > 0)
  {
    rangeTemp /= 2;
    msb++;
  }

  int bitMask = 1 << (msb - 1);
  
  int result = 0;
  int setMask = 1;
  while (bitMask > 0)
  {
    if (value & bitMask)
    {
      result ^= setMask;
    }

    setMask <<= 1;
    bitMask >>= 1;
  }

  return result;
}
} // End of Fourier namespace
} // End of Elba namespace
