/**
* \file Submesh.hpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Class definition for Submesh.
*/

#include <glm/mat4x4.hpp> 

namespace Elba
{
/**
* \brief Submesh composed of triangles.
*/
class Submesh
{
public:
  /**
  * \brief Constructor
  */
  Submesh();

  /**
  * \brief Draws all the triangles of this submesh.
  * \param proj The projection matrix.
  * \param view The view matrix.
  * \param model The model matrix.
  */
  void Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model);

};
} // End of Elba namespace
