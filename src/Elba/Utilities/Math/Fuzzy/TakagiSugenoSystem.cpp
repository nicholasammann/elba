#include <algorithm>
#include "Elba/Utilities/Math/Fuzzy/TakagiSugenoSystem.hpp"

namespace Elba
{
TakagiSugenoSystem::TakagiSugenoSystem()
{
}

void TakagiSugenoSystem::AddRule(PiecewiseLinear antecedent, TS_Consequence consequence)
{
  mRules.push_back(std::make_pair(antecedent, consequence));
}

float TakagiSugenoSystem::CalculateSystemOutput(float x)
{
  float numerator = 0.0f;
  float denominator = 0.0f;

  for (auto& rule : mRules)
  {
    PiecewiseLinear ante = rule.first;
    TS_Consequence consq = rule.second;

    // calculate firing strength
    float firingStrength = std::max(ante.ValueAt(x), 0.0f);
    
    if (firingStrength > 0.0f)
    {
      // calculate rule output
      float ruleOutput = consq(firingStrength);

      // add to sums
      numerator += firingStrength * ruleOutput;
      denominator += firingStrength;
    }
  }

  // return final system output
  return numerator / denominator;
}
} // End of Elba namespace
