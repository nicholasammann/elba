#include <fstream>

#include "Elba/Graphics/OpenGL/ShaderTypes/OpenGLShader.hpp"

namespace Elba
{

OpenGLShader::OpenGLShader(std::string filename)
  : mPath("")
  , mShader(0)
{
  // read in vertex shader
  mShaderSource = ReadShader(filename);
}

const std::string& OpenGLShader::GetPath() const
{
  return mPath;
}

GLuint OpenGLShader::GetShaderId()
{
  return mShader;
}

const GLchar* OpenGLShader::ReadShader(const std::string& filename)
{
  std::string source;
  std::string line;

  std::ifstream file(filename);

  if (file.is_open())
  {
    while (std::getline(file, line))
    {
      if (!line.empty())
      {
        source += line + '\n';
      }
    }
    file.close();
  }

  char* sourceChar = new char[source.size() + 1];
  strcpy(sourceChar, source.data());

  sourceChar[source.size()] = '\0';

  return sourceChar;
}

} // End of Elba namespace
