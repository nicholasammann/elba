#include <vector>

#include "Elba/Utilities/Math/Fuzzy/FuzzySet.hpp"

namespace Elba
{
class FuzzyController
{
public:
  FuzzyController();

  void SetRules(const FuzzySet& antecedents, const FuzzySet& consequences);

  //void AddRule(FuzzySet antecedent, FuzzySet consequence, std::function<float(float ax, float by)> relation);

private:
  FuzzySet mAntecedents;
  FuzzySet mConsequences;
};
} // End of Elba namespace