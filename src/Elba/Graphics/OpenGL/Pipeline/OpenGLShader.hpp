#pragma once

#include <string>

#include <gl/glew.h>

namespace Elba
{

class OpenGLShader
{
public:
  OpenGLShader(std::string filename);

  const std::string& GetPath() const;

  GLuint GetShaderId();

protected:
  std::string mPath;

  GLuint mShader;
  const GLchar* mShaderSource;

  // reads in a shader from file
  const GLchar* ReadShader(const std::string& filename);

  bool VerifyShaderCompilation(std::string errorMessage) const;

};

} // End of Elba namespace

