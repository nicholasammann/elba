/**
* \file main.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Main function. Constructs Engine.
*/

#include "Tests/CoreTests.hpp"
#include "Tests/PhysicsTests.hpp"

#include "Engine.hpp"
#include "Core/CoreModule.hpp"
#include "Physics/PhysicsModule.hpp"

using namespace Elba;

/**
* \brief main function
*/
int main(int argc, char** argv)
{
  Engine* elba = new Engine(false);

  elba->Initialize();

  while (elba->IsRunning())
  {
    elba->Update();
  }

  elba->Shutdown();

  // Core Module tests //
  //CoreModule* coreModule = elba->GetCoreModule();
  //Test::Core::RunAllTests(coreModule);

  // Physics Module tests //
  //PhysicsModule* physicsModule = elba->GetPhysicsModule();
  //Test::Physics::RunAllTests(physicsModule);

  return 0;
}