/**
* \file PhysicsTests.hpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Function declarations for test functions for PhysicsModule.
*/

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
      /**
      * \brief Runs all tests for PhysicsModule.
      * \param physicsModule PhysicsModule that will be tested.
      */
      void RunAllTests(PhysicsModule* physicsModule);

      /**
      * \brief Creates 10 PhysicsTransforms.
      * \param physicsModule PhysicsModule that will be tested.
      */
      void CreatePhysicsTransforms1(PhysicsModule* physicsModule);

      /**
      * \brief Creates 100 PhysicsTransforms.
      * \param physicsModule PhysicsModule that will be tested.
      */
      void CreatePhysicsTransforms2(PhysicsModule* physicsModule);
      
      /**
      * \brief Creates 1000 PhysicsTransforms.
      * \param physicsModule PhysicsModule that will be tested.
      */
      void CreatePhysicsTransforms3(PhysicsModule* physicsModule);

      /**
      * \brief Creates 10,000 PhysicsTransforms.
      * \param physicsModule PhysicsModule that will be tested.
      */
      void CreatePhysicsTransforms4(PhysicsModule* physicsModule);
      
      /**
      * \brief Creates 100 PhysicsTransforms, sets and gets the WorldTranslation.
      * Tests to make sure the input and output are identical.
      * \param physicsModule PhysicsModule that will be tested.
      */
      void WorldTranslation(PhysicsModule* physicsModule);

      /**
      * \brief Creates 100 PhysicsTransforms, sets and gets the WorldScale.
      * Tests to make sure the input and output are identical.
      * \param physicsModule PhysicsModule that will be tested.
      */
      void WorldScale(PhysicsModule* physicsModule);

      /**
      * \brief Creates 100 PhysicsTransforms, sets and gets the WorldRotation.
      * Tests to make sure the input and output are identical.
      * \param physicsModule PhysicsModule that will be tested.
      */
      void WorldRotation(PhysicsModule* physicsModule);

      /**
      * \brief Creates an input number of PhysicsTransforms.
      * \param physicsModule PhysicsModule that will be tested.
      * \param numTransforms The number of PhysicsTransforms that will be created.
      */
      std::vector<UniquePtr<PhysicsTransform>> CreateTransforms(PhysicsModule* physicsModule, int numTransforms);
    }
  }
}