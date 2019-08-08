#include "Elba/Utilities/Math/Fuzzy/FuzzySet.hpp"

namespace Elba
{
FuzzySet::FuzzySet()
{
}

float FuzzySet::ValueAt(float x, std::function<float(float x, float y)> choose)
{
  float result = -1.0f;

  for (PiecewiseLinear& fn : mFunctions)
  {
    float val = fn.ValueAt(x);

    if (val >= 0.0f)
    {
      if (result < 0.0f)
      {
        result = val;
      }
      else
      {
        result = choose(result, val);
      }
    }
  }
  return result;
}

void FuzzySet::AddFunction(PiecewiseLinear function)
{
  if (function.GetNumPoints() > 2)
  {
    mFunctions.push_back(function);
  }
}

const std::vector<PiecewiseLinear>& FuzzySet::GetFunctions() const
{
  return mFunctions;
}
} // End of Elba namespace
