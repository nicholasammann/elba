#pragma once

#include <vector>

#include "Utilities/StdTypedefs.hpp"
#include "Physics/PhysicsForwardDeclarations.hpp"

namespace Elba
{
  namespace Test
  {
    namespace Physics
    {
      void RunAllTests(PhysicsModule* physicsModule);

      void CreatePhysicsTransforms1(PhysicsModule* physicsModule);
      void CreatePhysicsTransforms2(PhysicsModule* physicsModule);
      void CreatePhysicsTransforms3(PhysicsModule* physicsModule);
      void CreatePhysicsTransforms4(PhysicsModule* physicsModule);
      
      void WorldTranslation(PhysicsModule* physicsModule);
      void WorldScale(PhysicsModule* physicsModule);
      void WorldRotation(PhysicsModule* physicsModule);

      // helper functions
      std::vector<UniquePtr<PhysicsTransform>> CreateTransforms(PhysicsModule* physicsModule, int numTransforms);
    }
  }
}