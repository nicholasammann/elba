/**
* \file OpenGLFactory.cpp
* \author Nicholas Ammann
* \date 9/9/2018
* \brief Member function definitions for OpenGLFactory.
*/

#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLFactory.hpp"
#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"

namespace Elba
{
OpenGLFactory::OpenGLFactory(OpenGLModule* graphicsModule)
  : GraphicsFactory(graphicsModule)
{
}

UniquePtr<Mesh> OpenGLFactory::RequestMesh(std::string name)
{
  // check if mesh has already been loaded
  auto result = mLoadedMeshes.find(name);

  Mesh* originalCopy = nullptr;

  // if mesh hasn't been loaded
  if (result == mLoadedMeshes.end())
  {
    // load the mesh from file
    UniquePtr<OpenGLMesh> loadedMesh = LoadMesh(name);

    // store the loaded mesh for copying
    auto inserted = mLoadedMeshes.insert(std::make_pair(name, std::move(loadedMesh)));

    if (inserted.second)
    {
      originalCopy = inserted.first->second.get();
    }
  }
  else
  {
    originalCopy = result->second.get();
  }

  // make a copy of the loaded mesh
  UniquePtr<OpenGLMesh> mesh = NewUnique<OpenGLMesh>();

  return std::move(mesh);
}

UniquePtr<OpenGLMesh> OpenGLFactory::LoadMesh(std::string name)
{
  return std::move(NewUnique<OpenGLMesh>());
}

} // End of Elba namespace
