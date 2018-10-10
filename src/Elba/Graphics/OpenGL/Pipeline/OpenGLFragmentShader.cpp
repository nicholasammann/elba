#include "Elba/Graphics/OpenGL/Pipeline/OpenGLFragmentShader.hpp"

namespace Elba
{

OpenGLFragmentShader::OpenGLFragmentShader(std::string path)
  : OpenGLShader(path)
{
  // create a shader object
  mShader = glCreateShader(GL_FRAGMENT_SHADER);

  // attach fragment shader source code
  glShaderSource(mShader, 1, &mShaderSource, nullptr);

  // compile fragment shader
  glCompileShader(mShader);

  VerifyShaderCompilation("Fragment shader failed to compile");
}

} // End of Elba namespace
