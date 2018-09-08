/**
* \file CoreModule.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for CoreModule.
*/

#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Object.hpp"
#include "Elba/Engine.hpp"

namespace Elba
{
CoreModule::CoreModule(Engine* engine)
  : Module(engine)
  , mGameWorld(NewUnique<Object>(nullptr))
{
  mGameWorld->mCoreModule = this;
}

void CoreModule::Initialize()
{
}

void CoreModule::Update()
{
}

Object* CoreModule::GetGameWorld()
{
  return mGameWorld.get();
}

} // End of Elba namespace
