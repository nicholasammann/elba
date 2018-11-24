#pragma once

/**
* \file Submesh.hpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Class definition for Submesh.
*/

#include <vector>
#include <glm/mat4x4.hpp>

#include "Elba/Graphics/PointLight.hpp"

namespace Elba
{

/**
* \brief Represents one Vertex of a submesh
*/
struct Vertex
{
  glm::vec3 mPos;
  glm::vec3 mColor;
  glm::vec2 mTexCoords;
  glm::vec3 mNormal;

  Vertex() : mPos(glm::vec3()), mColor(glm::vec3()), mTexCoords(glm::vec2()) { }
};

/**
* \brief Represents one Face of a submesh
*/
struct Face
{
  union
  {
    struct
    {
      unsigned int a, b, c;
    };
    unsigned int mIndices[3];
  };

  Face(unsigned int aA, unsigned int aB, unsigned int aC) : a(aA), b(aB), c(aC) { }
};

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
  * \brief Initialize fn
  */
  virtual void Initialize() = 0;

  /**
  * \brief Draws all the triangles of this submesh.
  * \param proj The projection matrix.
  * \param view The view matrix.
  * \param model The model matrix.
  */
  virtual void Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model, const PointLight& light) = 0;

  /**
  * \brief Adds a Vertex to the Submesh.
  * \param x The x coordinate.
  * \param y The y coordinate.
  * \param z The z coordinate.
  */
  void AddVertex(float x, float y, float z);

  /**
  * \brief Adds a Face to the Submesh.
  * \param a Index of first vertex.
  * \param b Index of second vertex.
  * \param c Index of third vertex.
  */
  void AddFace(uint32_t a, uint32_t b, uint32_t c);

protected:
  std::vector<Vertex> mVertices;
  std::vector<Face> mFaces;
};

} // End of Elba namespace
