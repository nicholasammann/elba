/**
* \file Module.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Member function definitions for Module.
*/

#include "Elba/Framework/Module.hpp"
#include "Elba/Engine.hpp"

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

} // End of Elba namespace
