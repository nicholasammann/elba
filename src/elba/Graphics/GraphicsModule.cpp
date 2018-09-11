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
{
}

void GraphicsModule::RegisterForDraw(GlobalKey key, DrawCallback callback)
{
  mDrawCallbacks.emplace_back(std::make_pair(key, callback));
}

bool GraphicsModule::DeregisterForDraw(GlobalKey key)
{
  auto result = std::find_if(mDrawCallbacks.begin(), mDrawCallbacks.end(), 
  [key](const std::pair<GlobalKey, DrawCallback>& pair) 
  {
    if (key.ToStdString() == pair.first.ToStdString())
    {
      return true;
    }
    return false;
  });

  if (result != mDrawCallbacks.end())
  {
    mDrawCallbacks.erase(result);
    return true;
  }

  return false;
}

} // End of Elba namespace
