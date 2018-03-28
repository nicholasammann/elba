/**
* \file GraphicsFactory.hpp
* \author Nicholas Ammann
* \date 3/27/2018
* \brief Class definition for GraphicsFactory.
*/

#pragma once

#include "Utilities/StdTypedefs.hpp"
#include "Graphics/GraphicsForwardDeclarations.hpp"

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

    /**
    * \brief Constructs a Mesh and adds it to the graphics module.
    * \return The Mesh that was just created.
    */
    UniquePtr<Mesh> CreateMesh();

  private:
    GraphicsModule* mModule;

  };

}