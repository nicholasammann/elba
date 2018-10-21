#include "Elba/Graphics/OpenGL/Pipeline/OpenGLVertexShader.hpp"

namespace Elba
{

OpenGLVertexShader::OpenGLVertexShader(std::string path)
  : OpenGLShader(path)
{
  // create a shader object (return value is the id)
  mShader = glCreateShader(GL_VERTEX_SHADER);

  // attach vertex shader source code
  glShaderSource(mShader, 1, &mShaderSource, nullptr);

  // compile vertex shader
  glCompileShader(mShader);

  VerifyShaderCompilation("Vertex Shader failed to compile");
}

} // End of Elba namespace
