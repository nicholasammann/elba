#include <functional>
#include <vector>

#include "Elba/Utilities/Math/Fuzzy/PiecewiseLinear.hpp"

namespace Elba
{
class FuzzySet
{
public:
  FuzzySet();

  float ValueAt(float x, std::function<float(float x, float y)> compare);

  void AddFunction(PiecewiseLinear function);

  const std::vector<PiecewiseLinear>& GetFunctions() const;

private:
  std::vector<PiecewiseLinear> mFunctions;

};
} // End of Elba namespace
