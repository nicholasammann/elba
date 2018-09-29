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
}

void Engine::Update()
{
  mCoreModule->Update();
  mGraphicsModule->Update();
  mPhysicsModule->Update();
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
