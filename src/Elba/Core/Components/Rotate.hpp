#pragma once

#include "Elba/Core/Component.hpp"

namespace Elba
{

class Transform;

class Rotate : public Component
{
public:
  Rotate(Object* object);

  void Initialize() final;

  void Update(double dt) final;

  void SetRotateSpeed(float speed);
  void SetMoveSpeed(float speed);

private:
  Transform* mTransform;
  glm::vec3 mOrigPos;
  float mTimeSince;

  float mRotateSpeed;
  float mMoveSpeed;
};

} // End of Elba namespace

