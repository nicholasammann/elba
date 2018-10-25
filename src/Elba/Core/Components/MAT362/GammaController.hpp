#pragma once

#include "Elba/Core/Component.hpp"
#include "Elba/Utilities/Math/Fuzzy/FuzzyController.hpp"

namespace Elba
{
class GammaController : public Component
{
public:
  GammaController(Object* parent);
private:
  FuzzyController mController;
};
} // End of Elba namespace

/*
// For gamma correction

if image is dark, gamma should be low (g < 1)

if image is fine, gamma should be middle (g = 1)

if image is light, gamma should be high (g > 1)
*/




