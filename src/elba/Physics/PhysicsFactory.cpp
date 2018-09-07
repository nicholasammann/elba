/**
* \file PhysicsFactory.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for PhysicsFactory.
*/

#include "Physics/PhysicsModule.hpp"
#include "Physics/PhysicsFactory.hpp"
#include "Physics/PhysicsTransform.hpp"

namespace Elba
{
PhysicsFactory::PhysicsFactory(PhysicsModule* physicsModule)
  : mPhysicsModule(physicsModule)
{
}

UniquePtr<PhysicsTransform> PhysicsFactory::CreatePhysicsTransform()
{
  UniquePtr<PhysicsTransform> transform = NewUnique<PhysicsTransform>();

  // add transform to module
  mPhysicsModule->mPhysicsTransforms.push_back(transform.get());

  return std::move(transform);
}

} // End of Elba namespace
