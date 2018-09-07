/**
* \file PhysicsTransform.hpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for PhysicsTransform.
*/

#pragma once

#include "Framework/Module.hpp"
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Elba
{
/**
* \brief Represents position, rotation and scale of an object in physics system.
*/
class PhysicsTransform
{
public:
  /**
  * \brief Default constructor
  */
  PhysicsTransform();

  /**
  * \brief Alternate constructor
  * \param worldTrans Initial world translation.
  * \param worldScale Initial world scale.
  * \param worldRot Initial world rotation.
  */
  PhysicsTransform(glm::vec3 worldTrans, glm::vec3 worldScale, glm::quat worldRot);

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
  // world variables
  glm::vec3 mWorldTranslation;
  glm::vec3 mWorldScale;
  glm::quat mWorldRotation;

};

} // End of Elba namespace
