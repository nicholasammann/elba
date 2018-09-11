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
#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"

#include "Elba/Utilities/GlobalKey.hpp"

namespace Elba
{
class OpenGLModule;

/**
* \brief Handles creation of objects in GraphicsModule.
*/
class OpenGLFactory : public GraphicsFactory
{
public:
  /**
  * \brief Constructor
  */
  OpenGLFactory(OpenGLModule* glModule);

  /**
  * \brief Constructs a Mesh and adds it to the graphics module.
  * \param name The name of the fbx file.
  * \return The Mesh that was just created.
  */
  UniquePtr<OpenGLMesh> RequestMesh(std::string name);

private:
  Map<std::string, UniquePtr<OpenGLMesh> > mLoadedMeshes;

  /**
  * \brief Loads a mesh from file.
  * \param name The name of the fbx file.
  * \return The newly loaded Mesh.
  */
  UniquePtr<OpenGLMesh> LoadMesh(std::string name);

};

} // End of Elba namespace
