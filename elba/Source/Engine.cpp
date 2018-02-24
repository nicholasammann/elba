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
    : mCoreModule(NewUnique<CoreModule>())
    , mGraphicsModule(NewUnique<GraphicsModule>())
    , mPhysicsModule(NewUnique<PhysicsModule>())
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
}