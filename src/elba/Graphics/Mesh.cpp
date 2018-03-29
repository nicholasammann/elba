/**
* \file Mesh.cpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Member function definitions for Mesh.
*/

#include "Graphics/Mesh.hpp"

namespace Elba
{
  Mesh::Mesh()
  {
  }

  void Mesh::Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model)
  {
    for (UniquePtr<Submesh>& submesh : mSubmeshes)
    {
      submesh->Draw(proj, view, model);
    }
  }

  void Mesh::SetShader(const char* shaderName)
  {
  }
}