/**
* \file PhysicsFactory.hpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Class definition for PhysicsFactory.
*/

#pragma once

#include "Utilities/StdTypedefs.hpp"
#include "Physics/PhysicsForwardDeclarations.hpp"

namespace Elba
{
  /**
  * \brief Handles creation of objects in PhysicsModule.
  */
  class PhysicsFactory
  {
  public:
    /**
    * \brief Constructor
    */
    PhysicsFactory(PhysicsModule* physicsModule);

    /**
    * \brief Constructs a transform and adds it to the physics system.
    * \return The PhysicsTransform that was just created.
    */
    UniquePtr<PhysicsTransform> CreatePhysicsTransform();

  private:
    PhysicsModule* mPhysicsModule;

  };

}