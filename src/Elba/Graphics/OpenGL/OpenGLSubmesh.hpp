#pragma once

#include "Elba/Graphics/OpenGL/OpenGLShader.hpp"
#include "Elba/Graphics/Submesh.hpp"

namespace Elba
{

class OpenGLSubmesh : public Submesh
{
public:
  OpenGLSubmesh();

  void Initialize() final;

  void Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model) final;

  /**
  * \brief Sets the shader this mesh will use to draw.
  * \param shader A shader for the submesh to use.
  */
  void SetShader(OpenGLShader* shader);

private:
  unsigned int mVAO;
  unsigned int mVBO;
  unsigned int mEBO;

  OpenGLShader* mShader;
};

} // End of Elba namespace
