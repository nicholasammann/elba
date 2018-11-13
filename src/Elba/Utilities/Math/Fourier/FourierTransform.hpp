#include <vector>

namespace Elba
{
namespace Fourier
{

typedef std::vector<std::vector<int> > SpatialImage;
typedef std::vector<std::vector<ComplexNumber> > FrequencyImage;

struct ComplexNumber
{
  ComplexNumber(int r, int i);
  double real;
  double imaginary;
};

void Direct(const SpatialImage& input, FrequencyImage& output);

void Separable(const SpatialImage& input, FrequencyImage& output);

} // End of Fourier namespace
} // End of Elba namespace
