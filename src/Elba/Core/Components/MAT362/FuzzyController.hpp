#pragma once

#include <vector>

#include <glm/vec2.hpp>

#include "Elba/Core/Component.hpp"

namespace Elba
{

class PiecewiseLinear
{
public:
  PiecewiseLinear();

  float ValueAt(float x);

  void AddPoint(glm::vec2 point);
  void ClearPoints();

  unsigned int GetNumPoints() const;

private:
  std::vector<glm::vec2> mPoints;
};

class FuzzySet
{
public:
  FuzzySet();

  float ValueAt(float x, std::function<float(float x, float y)> compare);

  void AddFunction(PiecewiseLinear function);

private:
  std::vector<PiecewiseLinear> mFunctions;

};

class FuzzyController : public Component
{
public:
  FuzzyController(Object* parent);

private:
  std::vector<FuzzySet> mRules;

};
} // End of Elba namespace
