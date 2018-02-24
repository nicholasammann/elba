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

namespace ELBA
{
  Engine::Engine()
    : mCoreModule(NewUnique<CoreModule>())
    , mGraphicsModule(NewUnique<GraphicsModule>())
    , mPhysicsModule(NewUnique<PhysicsModule>())
  {
  }

  Engine::~Engine()
  {
  }

  void Engine::Initialize()
  {
  }
}