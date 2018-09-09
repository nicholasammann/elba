/**
* \file Mesh.cpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Member function definitions for Mesh.
*/

#include "Elba/Graphics/Mesh.hpp"

namespace Elba
{
Mesh::Mesh()
{
}

void Mesh::Initialize()
{
  for (UniquePtr<Submesh>& submesh : mSubmeshes)
  {
    submesh->Initialize();
  }
}

void Mesh::Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model)
{
  for (UniquePtr<Submesh>& submesh : mSubmeshes)
  {
    submesh->Draw(proj, view, model);
  }
}

} // End of Elba namespace
