/**
* \file Submesh.cpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Member function definitions for Submesh.
*/

#include "Elba/Graphics/Submesh.hpp"

namespace Elba
{
Submesh::Submesh()
{
}

void Submesh::AddVertex(float aX, float aY, float aZ)
{
  Vertex v;
  v.mPos.x = aX;
  v.mPos.y = aY;
  v.mPos.z = aZ;

  mVertices.push_back(v);
}

void Submesh::AddFace(uint32_t a, uint32_t b, uint32_t c)
{
  mFaces.push_back(Face(a, b, c));
}

} // End of Elba namespace
