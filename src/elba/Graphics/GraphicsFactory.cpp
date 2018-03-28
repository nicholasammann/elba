/**
* \file GraphicsFactory.cpp
* \author Nicholas Ammann
* \date 2/27/2018
* \brief Member function definitions for GraphicsFactory.
*/

#include "Graphics/GraphicsModule.hpp"
#include "Graphics/GraphicsFactory.hpp"
#include "Graphics/Mesh.hpp"

namespace Elba
{
  GraphicsFactory::GraphicsFactory(GraphicsModule* graphicsModule)
    : mModule(graphicsModule)
  {
  }

  UniquePtr<Mesh> GraphicsFactory::CreateMesh()
  {
    UniquePtr<Mesh> mesh = NewUnique<Mesh>();

    mModule->mMeshes.push_back(mesh.get());

    return std::move(mesh);
  }
}