#pragma once

#include "Elba/Graphics/OpenGL/OpenGLShader.hpp"
#include "Elba/Graphics/Submesh.hpp"

namespace Elba
{

class OpenGLTexture;

class OpenGLSubmesh : public Submesh
{
public:
  /**
  * \brief Constructor
  */
  OpenGLSubmesh();

  /**
  * \brief Constructor
  * \param verts The vertices of this submesh.
  * \param faces The faces of this submesh.
  */
  OpenGLSubmesh(const std::vector<Vertex>& verts, const std::vector<Face>& faces);

  /**
  * \brief Initialize fn
  */
  void Initialize() final;

  /**
  * \brief Draws all the triangles of this submesh.
  * \param proj The projection matrix.
  * \param view The view matrix.
  * \param model The model matrix.
  */
  void Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model) final;

  /**
  * \brief Sets the shader this mesh will use to draw.
  * \param shader A shader for the submesh to use.
  */
  void SetShader(OpenGLShader* shader);

  /**
  * \brief Loads the diffuse texture for this submesh
  * \param path The texture file.
  */
  void LoadTexture(const std::string& path);
  
  void LoadTexture(OpenGLTexture* texture);

  OpenGLTexture* GetDiffuseTexture() const;

private:
  unsigned int mVAO;
  unsigned int mVBO;
  unsigned int mEBO;

  OpenGLShader* mShader;

  OpenGLTexture* mDiffuseTexture;
};

} // End of Elba namespace
