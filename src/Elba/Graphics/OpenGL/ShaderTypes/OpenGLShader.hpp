#pragma once

#include <string>

#include <gl/glew.h>

namespace Elba
{

class OpenGLShader
{
  OpenGLShader(std::string filename);

  const std::string& GetPath() const;

protected:
  std::string mPath;

  const GLchar* mShaderSource;

  // reads in a shader from file
  const GLchar* ReadShader(const std::string& filename);

};

} // End of Elba namespace

