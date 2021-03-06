#pragma once

/**
* \file Mesh.hpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Class definition for Mesh.
*/

#include <glm/mat4x4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Elba/Utilities/StdTypedefs.hpp"
#include "Elba/Utilities/GlobalKey.hpp"

#include "Elba/Graphics/GraphicsForwardDeclarations.hpp"

#include "Elba/Graphics/PointLight.hpp"
#include "Elba/Graphics/Submesh.hpp"

namespace Elba
{
/**
* \brief Mesh that contains Submeshes.
*/
class Mesh
{
public:
  /**
  * \brief Constructor
  */
  Mesh();

  /**
  * \brief Initialize.
  */
  virtual void Initialize() = 0;

  /**
  * \brief Draws the Mesh.
  * \param proj The projection matrix.
  * \param view The view matrix.
  * \param model The model matrix.
  */
  virtual void Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model, const PointLight& light) = 0;

  virtual void LoadMesh(std::string path) = 0;

  virtual void LoadShader(std::string name) = 0;
};

} // End of Elba namespace
