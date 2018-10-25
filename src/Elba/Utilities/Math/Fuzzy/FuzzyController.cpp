#include "Elba/Utilities/Math/Fuzzy/FuzzyController.hpp"

namespace Elba
{
FuzzyController::FuzzyController()
{
}

void FuzzyController::SetRules(const FuzzySet& antecedents, const FuzzySet& consequences)
{
  if (antecedents.GetFunctions().size() == consequences.GetFunctions().size())
  {
    mAntecedents = antecedents;
    mConsequences = consequences;
  }
  else
  {
    throw "Antecedents and Consequences have different sizes";
  }
}

/*
void FuzzyController::AddRule(FuzzySet antecedent, 
                              FuzzySet consequence, 
                              std::function<float(float ax, float by)> relation)
{

}
*/
} // End of Elba namespace
