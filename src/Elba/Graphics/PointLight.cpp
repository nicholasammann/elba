#include "Elba/Graphics/PointLight.hpp"

namespace Elba
{
PointLight::PointLight()
  : mPosition(glm::vec3(0.0f))
  , mIntensity(1.0f)
{
}

void PointLight::SetIntensity(float value)
{
  if (value > 1.0f)
  {
    value = 1.0f;
  }
  else if (value < 0.0f)
  {
    value = 0.0f;
  }

  mIntensity = value;
}

float PointLight::GetIntensity() const
{
  return mIntensity;
}

void PointLight::SetPosition(glm::vec3 position)
{
  mPosition = position;
}

glm::vec3 PointLight::GetPosition() const
{
  return mPosition;
}
} // End of Elba namespace
