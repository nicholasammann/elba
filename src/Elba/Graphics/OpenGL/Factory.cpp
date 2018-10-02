/**
* \file OpenGLFactory.cpp
* \author Nicholas Ammann
* \date 9/9/2018
* \brief Member function definitions for OpenGLFactory.
*/

#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/Factory.hpp"
#include "Elba/Graphics/OpenGL/Mesh.hpp"

#include "Elba/Utilities/Utils.hpp"

namespace Elba
{
namespace OpenGL
{
Factory::Factory(OpenGLModule* graphicsModule)
  : GraphicsFactory(graphicsModule)
{
  mLoadedMeshes.clear();
}

UniquePtr<Mesh> Factory::RequestMesh(std::string name)
{
  // check if mesh has already been loaded
  auto result = mLoadedMeshes.find(name);

  Mesh* originalCopy = nullptr;

  // if mesh hasn't been loaded
  if (result == mLoadedMeshes.end())
  {
    // load the mesh from file
    UniquePtr<Mesh> loadedMesh = LoadMesh(name);

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
  UniquePtr<Mesh> mesh(new Mesh(*originalCopy));

  return std::move(mesh);
}

UniquePtr<Mesh> Factory::LoadMesh(std::string name)
{
  std::string assetsDir = Utils::GetAssetsDirectory();
  std::string asset = assetsDir + "/Models/" + name;

  UniquePtr<Mesh> mesh = NewUnique<Mesh>();
  mesh->LoadMesh(asset);

  return std::move(mesh);
}
} // End of OpenGL namespace
} // End of Elba namespace
