/**
* \file CoreModule.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for CoreModule.
*/

#include "Core/CoreModule.hpp"
#include "Core/Object.hpp"

namespace Elba
{
  CoreModule::CoreModule()
    : mGameWorld(NewUnique<Object>(nullptr))
  {

  }

  void CoreModule::Initialize()
  {
  }

  void CoreModule::Update()
  {
  }

  Object * CoreModule::GetGameWorld()
  {
    return mGameWorld.get();
  }
}

