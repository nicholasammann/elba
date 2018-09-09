/**
* \file Mesh.hpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Class definition for Mesh.
*/

#include <glm/mat4x4.hpp>

#include "Elba/Utilities/StdTypedefs.hpp"

#include "Elba/Graphics/GraphicsForwardDeclarations.hpp"

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
  * \brief Initializes all contained submeshes.
  */
  void Initialize();

  /**
  * \brief Draws all submeshes contained by this Mesh.
  * \param proj The projection matrix.
  * \param view The view matrix.
  * \param model The model matrix.
  */
  void Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model);

private:
  std::vector<UniquePtr<Submesh>> mSubmeshes;
};

} // End of Elba namespace
