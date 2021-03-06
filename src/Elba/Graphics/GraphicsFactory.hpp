/**
* \file GraphicsFactory.hpp
* \author Nicholas Ammann
* \date 3/27/2018
* \brief Class definition for GraphicsFactory.
*/

#pragma once

#include "Elba/Utilities/StdTypedefs.hpp"
#include "Elba/Graphics/GraphicsForwardDeclarations.hpp"

#include "Elba/Graphics/Mesh.hpp"

#include "Elba/Utilities/GlobalKey.hpp"

namespace Elba
{
/**
* \brief Handles creation of objects in GraphicsModule.
*/
class GraphicsFactory
{
public:
  /**
  * \brief Constructor
  */
  GraphicsFactory(GraphicsModule* graphicsModule);

private:
  GraphicsModule* mModule;
};

} // End of Elba namespace
