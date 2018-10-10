#include "Elba/Graphics/OpenGL/ShaderTypes/OpenGLVertexShader.hpp"

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

  // check if vertex shader compiled correctly
  int success;
  char infoLog[512] = { '\0' };
  glGetShaderiv(mShader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(mShader, 512, nullptr, infoLog);
    std::string error = std::string(path) + " : (Vertex Shader compilation failed) : " + std::string(infoLog);
    throw error;
  }
}

} // End of Elba namespace
