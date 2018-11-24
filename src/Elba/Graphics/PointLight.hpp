#pragma once

#include "glm/vec3.hpp"

namespace Elba
{
class PointLight
{
public:
  PointLight();

  void SetIntensity(float value);
  float GetIntensity() const;

  void SetPosition(glm::vec3 position);
  glm::vec3 GetPosition() const;

private:
  glm::vec3 mPosition;
  float mIntensity;
};
} // End of Elba namespace
