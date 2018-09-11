#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Elba
{
class Camera
{
public:
  Camera();

  void UpdateVectors();

  glm::mat4 ConstructViewMatrix();

  glm::mat4 ConstructProjMatrix(int aWidth, int aHeight);

  void SetPosition(glm::vec3 aPos);

  void SetTargetPoint(glm::vec3 aPoint);

  glm::vec3 mPosition;
  glm::vec3 mTarget;
  glm::vec3 mDirection;
  glm::vec3 mWorldUp;
  glm::vec3 mCameraUp;
  glm::vec3 mCameraRight;
};

} // End of Elba namespace

