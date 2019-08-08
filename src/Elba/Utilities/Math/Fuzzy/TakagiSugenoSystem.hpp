#include <vector>

#include "Elba/Utilities/Math/Fuzzy/FuzzySet.hpp"


namespace Elba
{
typedef std::function<float(float)> TS_Consequence;
typedef std::pair<PiecewiseLinear, TS_Consequence> TS_Rule;

class TakagiSugenoSystem
{
public:
  TakagiSugenoSystem();

  void AddRule(PiecewiseLinear antecedent, TS_Consequence consequence);

  float CalculateSystemOutput(float x);

private:
  std::vector<TS_Rule> mRules;
};
} // End of Elba namespace