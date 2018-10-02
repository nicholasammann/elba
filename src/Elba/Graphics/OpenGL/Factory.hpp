/**
* \file OpenGLFactory.hpp
* \author Nicholas Ammann
* \date 9/9/2018
* \brief Class definition for OpenGLFactory.
*/

#pragma once

#include "Elba/Utilities/StdTypedefs.hpp"
#include "Elba/Graphics/GraphicsForwardDeclarations.hpp"

#include "Elba/Graphics/GraphicsFactory.hpp"
#include "Elba/Graphics/OpenGL/Mesh.hpp"

#include "Elba/Utilities/GlobalKey.hpp"

namespace Elba
{
namespace OpenGL
{
class OpenGLModule;

/**
* \brief Handles creation of objects in GraphicsModule.
*/
class Factory : public GraphicsFactory
{
public:
  /**
  * \brief Constructor
  */
  Factory(OpenGLModule* glModule);

  /**
  * \brief Constructs a Mesh and adds it to the graphics module.
  * \param name The name of the fbx file.
  * \return The Mesh that was just created.
  */
  UniquePtr<Mesh> RequestMesh(std::string name);

private:
  Map<std::string, UniquePtr<Mesh> > mLoadedMeshes;

  /**
  * \brief Loads a mesh from file.
  * \param name The name of the fbx file.
  * \return The newly loaded Mesh.
  */
  UniquePtr<Mesh> LoadMesh(std::string name);

};
} // End of OpenGL namespace
} // End of Elba namespace
