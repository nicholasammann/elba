#include "Elba/Graphics/OpenGL/ShaderTypes/OpenGLFragmentShader.hpp"

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

  // check if fragment shader compiled correctly
  int success;
  char infoLog[512] = { '\0' };
  glGetShaderiv(mShader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(mShader, 512, nullptr, infoLog);
    std::string error = std::string(path) + " : (Fragment Shader compilation failed) : " + std::string(infoLog);
    throw error;
  }
}

} // End of Elba namespace
