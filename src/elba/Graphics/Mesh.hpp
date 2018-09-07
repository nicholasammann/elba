/**
* \file Mesh.hpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Class definition for Mesh.
*/

#include <glm/mat4x4.hpp>
#include "Utilities/StdTypedefs.hpp"

#include "Graphics/GraphicsForwardDeclarations.hpp"

#include "Graphics/Submesh.hpp"

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
  * \brief Draws all submeshes contained by this Mesh.
  * \param proj The projection matrix.
  * \param view The view matrix.
  * \param model The model matrix.
  */
  void Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model);

  /**
  * \brief Sets the shader this mesh will use to draw.
  * \param shaderName The name of the shader that will be used.
  */
  void SetShader(const char* shaderName);

private:
  std::vector<UniquePtr<Submesh>> mSubmeshes;
};

} // End of Elba namespace
