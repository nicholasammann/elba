/**
* \file Transform.hpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Class definition for Transform.
*/

#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Utilities/StdTypedefs.hpp"

#include "Core/Component.hpp"
#include "Physics/PhysicsForwardDeclarations.hpp"

namespace Elba
{
/**
* \brief Interface for communicating with a transform object in the physics module.
*/
class Transform : public Component
{
public:
  /**
  * \brief Constructor
  * \param parent The parent object.
  */
  Transform(Object* parent);

  /**
  * \brief Initializes derived class.
  */
  void Initialize() override;

  /**
  * \brief Sets the world position.
  * \param worldTrans The new world translation.
  */
  void SetWorldTranslation(const glm::vec3& worldTrans);

  /**
  * \brief Gets the world position.
  * \return The current world translation.
  */
  const glm::vec3& GetWorldTranslation() const;

  /**
  * \brief Sets the world scale.
  * \param worldScale The new world scale.
  */
  void SetWorldScale(const glm::vec3& worldScale);

  /**
  * \brief Gets the world scale.
  * \return The current world scale.
  */
  const glm::vec3& GetWorldScale() const;

  /**
  * \brief Sets the world rotation.
  * \param worldRot The new world rotation.
  */
  void SetWorldRotation(const glm::quat& worldRot);

  /**
  * \brief Gets the world rotation.
  * \return The current world rotation.
  */
  const glm::quat& GetWorldRotation() const;

private:
  UniquePtr<PhysicsTransform> mPhysicsTransform;

};

} // End of Elba namespace
