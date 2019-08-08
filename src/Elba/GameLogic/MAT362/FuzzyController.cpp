#include <algorithm>
#include <functional>

#include "FuzzyController.hpp"

namespace Elba
{
PiecewiseLinear::PiecewiseLinear()
{
}

float PiecewiseLinear::ValueAt(float x)
{
  for (int i = 0; i < mPoints.size() - 1; ++i)
  {
    if (x > mPoints[i].x)
    {
      // calculate the line from i to i+1
      float slope = (mPoints[i + 1].y - mPoints[i].y) / (mPoints[i + 1].x - mPoints[i].x);

      return mPoints[i].y + (x - mPoints[i].x) * slope;
    }
  }
  return -1.0f;
}

void PiecewiseLinear::AddPoint(glm::vec2 point)
{
  if (point.y >= 0.0f)
  {
    // add point
    mPoints.push_back(point);

    // sort based on x value
    std::sort(mPoints.begin(), mPoints.end(), [point](const glm::vec2& rhs) { return point.x < rhs.x; });
  }
  else
  {
    throw "Trying to add invalid point, y < 0";
  }
}

void PiecewiseLinear::ClearPoints()
{
  mPoints.clear();
}

unsigned int PiecewiseLinear::GetNumPoints() const
{
  return mPoints.size();
}

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

FuzzyController::FuzzyController(Object* parent) : Component(parent)
{
}

} // End of Elba namespace
