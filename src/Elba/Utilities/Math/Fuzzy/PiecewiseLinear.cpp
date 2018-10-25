#include <algorithm>

#include "Elba/Utilities/Math/Fuzzy/PiecewiseLinear.hpp"

namespace Elba
{

PiecewiseLinear::PiecewiseLinear()
{
}

float PiecewiseLinear::ValueAt(float x) const
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
    std::sort(mPoints.begin(), mPoints.end(), [](const glm::vec2& lhs, const glm::vec2& rhs) { return lhs.x < rhs.x; });
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

} // End of Elba namespace
