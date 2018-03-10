#include <iostream>

#include "PhysicsTests.hpp"

#include "Physics/PhysicsModule.hpp"
#include "Physics/PhysicsFactory.hpp"
#include "Physics/PhysicsTransform.hpp"

#include "Tests/TestHelpers.hpp"

namespace Elba
{
  namespace Test
  {
    namespace Physics
    {
      void RunAllTests(PhysicsModule* physicsModule)
      {
        // Creating physics transforms
        CreatePhysicsTransforms1(physicsModule);
        CreatePhysicsTransforms2(physicsModule);
        CreatePhysicsTransforms3(physicsModule);
        CreatePhysicsTransforms4(physicsModule);

        // Setting and Getting basic properties
        WorldTranslation(physicsModule);
        WorldScale(physicsModule);
        WorldRotation(physicsModule);
      }

      void CreatePhysicsTransforms1(PhysicsModule* physicsModule)
      {
        PrintTestHeader("Create Physics Transforms 1");
        std::vector<UniquePtr<PhysicsTransform>> transforms = CreateTransforms(physicsModule, 10);
        PrintTestFooter();
      }

      void CreatePhysicsTransforms2(PhysicsModule* physicsModule)
      {
        PrintTestHeader("Create Physics Transforms 2");
        std::vector<UniquePtr<PhysicsTransform>> transforms = CreateTransforms(physicsModule, 100);
        PrintTestFooter();
      }

      void CreatePhysicsTransforms3(PhysicsModule* physicsModule)
      {
        PrintTestHeader("Create Physics Transforms 3");
        std::vector<UniquePtr<PhysicsTransform>> transforms = CreateTransforms(physicsModule, 1000);
        PrintTestFooter();
      }

      void CreatePhysicsTransforms4(PhysicsModule* physicsModule)
      {
        PrintTestHeader("Create Physics Transforms 4");
        std::vector<UniquePtr<PhysicsTransform>> transforms = CreateTransforms(physicsModule, 10000);
        PrintTestFooter();
      }

      void WorldTranslation(PhysicsModule* physicsModule)
      {
        PrintTestHeader("World Translation");

        std::vector<UniquePtr<PhysicsTransform>> transforms = CreateTransforms(physicsModule, 100);

        for (int i = 0; i < 100; i++)
        {
          glm::vec3 input(i, 2 * i, 3 * i);

          transforms[i]->SetWorldTranslation(input);

          glm::vec3 output = transforms[i]->GetWorldTranslation();

          if (input != output)
          {
            throw std::exception("Mismatch between input and output when testing WorldTranslation on PhysicsTransform.");
          }
        }

        PrintTestFooter();
      }

      void WorldScale(PhysicsModule* physicsModule)
      {
        PrintTestHeader("World Scale");

        std::vector<UniquePtr<PhysicsTransform>> transforms = CreateTransforms(physicsModule, 100);

        for (int i = 0; i < 100; i++)
        {
          glm::vec3 input(i, 2 * i, 3 * i);

          transforms[i]->SetWorldScale(input);

          glm::vec3 output = transforms[i]->GetWorldScale();

          if (input != output)
          {
            throw std::exception("Mismatch between input and output when testing WorldScale on PhysicsTransform.");
          }
        }

        PrintTestFooter();
      }

      void WorldRotation(PhysicsModule* physicsModule)
      {
        PrintTestHeader("World Rotation");

        std::vector<UniquePtr<PhysicsTransform>> transforms = CreateTransforms(physicsModule, 100);

        for (int i = 0; i < 100; i++)
        {
          glm::quat input(0.25f, 0.5f, 0.75f, 1.0f);

          transforms[i]->SetWorldRotation(input);

          glm::quat output = transforms[i]->GetWorldRotation();

          if (input != output)
          {
            throw std::exception("Mismatch between input and output when testing WorldRotation on PhysicsTransform.");
          }
        }

        PrintTestFooter();
      }

      std::vector<UniquePtr<PhysicsTransform>> CreateTransforms(PhysicsModule* physicsModule, int numTransforms)
      {
        PhysicsFactory* factory = physicsModule->GetFactory();

        std::vector<UniquePtr<PhysicsTransform>> result(numTransforms);

        for (int i = 0; i < numTransforms; i++)
        {
          result[i] = factory->CreatePhysicsTransform();
          std::cout << "Created PhysicsTransform " << i << std::endl;
        }

        return std::move(result);
      }
    }
  }
  

  
}


