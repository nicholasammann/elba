/**
* \file GraphicsFactory.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for GraphicsFactory.
*/

#include "Elba/Graphics/GraphicsModule.hpp"
#include "Elba/Graphics/GraphicsFactory.hpp"
#include "Elba/Graphics/Mesh.hpp"

namespace Elba
{
GraphicsFactory::GraphicsFactory(GraphicsModule* graphicsModule)
  : mModule(graphicsModule)
{
}

} // End of Elba namespace
