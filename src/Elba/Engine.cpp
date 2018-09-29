/**
* \file Engine.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for Engine.
*/

#include <iostream>

#include "Elba/Core/CoreModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Physics/PhysicsModule.hpp"

#include "Elba/Engine.hpp"

namespace Elba
{
Engine::Engine(bool inEditorMode)
  : mCoreModule(NewUnique<CoreModule>(this))
  , mGraphicsModule(NewUnique<OpenGLModule>(this))
  , mPhysicsModule(NewUnique<PhysicsModule>(this))
  , mIsRunning(true)
  , mInEditorMode(inEditorMode)
  , mPreviousTime(std::chrono::high_resolution_clock::now())
{
}

Engine::~Engine()
{
}

void Engine::Initialize()
{
  // initialize all modules
  mCoreModule->Initialize();
  mGraphicsModule->Initialize();
  mPhysicsModule->Initialize();

  mPreviousTime = std::chrono::high_resolution_clock::now();
}

void Engine::Update()
{
  std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> delta = std::chrono::duration_cast<std::chrono::duration<double> >(time - mPreviousTime);
  double dt = delta.count();

  mPreviousTime = time;

  mCoreModule->Update(dt);
  mGraphicsModule->Update(dt);
  mPhysicsModule->Update(dt);
}

void Engine::Shutdown()
{
}

bool Engine::IsRunning() const
{
  return mIsRunning;
}

CoreModule* Engine::GetCoreModule()
{
  return mCoreModule.get();
}

GraphicsModule* Engine::GetGraphicsModule()
{
  return mGraphicsModule.get();
}

PhysicsModule* Engine::GetPhysicsModule()
{
  return mPhysicsModule.get();
}

bool Engine::InEditor() const
{
  return mInEditorMode;
}

} // End of Elba namespace
