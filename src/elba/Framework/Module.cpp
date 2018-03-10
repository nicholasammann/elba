/**
* \file Module.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for Module.
*/

#include "Framework/Module.hpp"
#include "Engine.hpp"

namespace Elba
{
  Module::Module(Engine* engine)
    : mEngine(engine)
  {
  }

  Engine* Module::GetEngine() const
  {
    return mEngine;
  }

}