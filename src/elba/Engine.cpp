/**
* \file Engine.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for Engine.
*/

#include <iostream>

#include "Core/CoreModule.hpp"
#include "Graphics/GraphicsModule.hpp"
#include "Physics/PhysicsModule.hpp"

#include "Engine.hpp"

namespace Elba
{
  Engine::Engine()
    : mCoreModule(NewUnique<CoreModule>(this))
    , mGraphicsModule(NewUnique<GraphicsModule>(this))
    , mPhysicsModule(NewUnique<PhysicsModule>(this))
    , mIsRunning(true)
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
}