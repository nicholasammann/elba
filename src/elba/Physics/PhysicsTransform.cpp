/**
* \file PhysicsTransform.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for PhysicsTransform.
*/

#include "Elba/Physics/PhysicsTransform.hpp"

namespace Elba
{
PhysicsTransform::PhysicsTransform()
  : mWorldTranslation()
  , mWorldScale(1.0f, 1.0f, 1.0f)
  , mWorldRotation()
{
}

PhysicsTransform::PhysicsTransform(glm::vec3 worldTrans,
                                   glm::vec3 worldScale,
                                   glm::quat worldRot)
  : mWorldTranslation(worldTrans)
  , mWorldScale(worldScale)
  , mWorldRotation(worldRot)
{
}

void PhysicsTransform::SetWorldTranslation(const glm::vec3& worldTrans)
{
  mWorldTranslation = worldTrans;
}

const glm::vec3& PhysicsTransform::GetWorldTranslation() const
{
  return mWorldTranslation;
}

void PhysicsTransform::SetWorldScale(const glm::vec3& worldScale)
{
  mWorldScale = worldScale;
}

const glm::vec3& PhysicsTransform::GetWorldScale() const
{
  return mWorldScale;
}

void PhysicsTransform::SetWorldRotation(const glm::quat& worldRot)
{
  mWorldRotation = worldRot;
}

const glm::quat& PhysicsTransform::GetWorldRotation() const
{
  return mWorldRotation;
}

} // End of Elba namespace
