/**
* \file GraphicsModule.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for GraphicsModule.
*/

#include <iostream>

#include "Elba/Engine.hpp"

#include "Elba/Graphics/GraphicsModule.hpp"

namespace Elba
{
GraphicsModule::GraphicsModule(Engine* engine)
  : Module(engine)
  , mFactory(NewUnique<GraphicsFactory>(this))
{
}

GraphicsFactory* GraphicsModule::GetFactory() const
{
  return mFactory.get();
}

} // End of Elba namespace
