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
#include "Elba/Core/Components/Rotate.hpp"

using namespace Elba;

/**
* \brief main function
*/
int main(int argc, char** argv)
{
  Engine* elba = new Engine(false);

  elba->Initialize();

  // Test Level
  Elba::CoreModule* core = elba->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();

  Elba::Object* object = level->CreateChild();

  // Add components
  Elba::Transform* transform = object->AddComponent<Elba::Transform>();
  transform->SetWorldTranslation(glm::vec3(0.0f, -10.0f, 0.0f));
  transform->SetWorldRotation(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));
  transform->SetWorldScale(glm::vec3(1.0f));

  Elba::Model* model = object->AddComponent<Elba::Model>();
  model->LoadMesh("crysis/nanosuit.obj");
  model->LoadShader("textured");

  Elba::Rotate* rotate = object->AddComponent<Elba::Rotate>();

  transform->Initialize();
  model->Initialize();
  rotate->Initialize();
  ////////////////////////

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