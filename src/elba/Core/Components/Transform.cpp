/**
* \file Transform.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for Transform.
*/

#include "Engine.hpp"
#include "Core/Components/Transform.hpp"
#include "Core/Object.hpp"
#include "Core/CoreModule.hpp"

#include "Physics/PhysicsModule.hpp"
#include "Physics/PhysicsFactory.hpp"
#include "Physics/PhysicsTransform.hpp"

namespace Elba
{
  Transform::Transform(Object* parent) : Component(parent)
  {
    // ask physics module to create transform object
    CoreModule* coreModule = parent->GetCoreModule();
    Engine* engine = coreModule->GetEngine();
    PhysicsModule* physicsModule = engine->GetPhysicsModule();
    PhysicsFactory* physicsFactory = physicsModule->GetFactory();

    mPhysicsTransform = physicsFactory->CreatePhysicsTransform();
  }

  void Transform::Initialize()
  {
  }

  void Transform::SetWorldTranslation(const glm::vec3& worldTrans)
  {
    mPhysicsTransform->SetWorldTranslation(worldTrans);
  }

  const glm::vec3& Transform::GetWorldTranslation() const
  {
    return mPhysicsTransform->GetWorldTranslation();
  }

  void Transform::SetWorldScale(const glm::vec3& worldScale)
  {
    mPhysicsTransform->SetWorldScale(worldScale);
  }

  const glm::vec3& Transform::GetWorldScale() const
  {
    return mPhysicsTransform->GetWorldScale();
  }

  void Transform::SetWorldRotation(const glm::quat& worldRot)
  {
    mPhysicsTransform->SetWorldRotation(worldRot);
  }

  const glm::quat& Transform::GetWorldRotation() const
  {
    return mPhysicsTransform->GetWorldRotation();
  }
}