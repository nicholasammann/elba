/**
* \file PhysicsFactory.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for PhysicsFactory.
*/

#include "Physics/PhysicsFactory.hpp"
#include "Physics/PhysicsTransform.hpp"

namespace Elba
{
  PhysicsFactory::PhysicsFactory()
  {
  }

  UniquePtr<PhysicsTransform> PhysicsFactory::CreatePhysicsTransform()
  {
    return std::move(NewUnique<PhysicsTransform>());
  }
}