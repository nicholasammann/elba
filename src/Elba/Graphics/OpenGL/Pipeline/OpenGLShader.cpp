#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <fstream>

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLShader.hpp"

namespace Elba
{

OpenGLShader::OpenGLShader(std::string filename)
  : mPath(filename)
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
  else
  {
    throw std::exception("THE FILE DIDN'T LOAD, RED ALERT, RED ALERT");
  }

  char* sourceChar = new char[source.size() + 1];
  strcpy(sourceChar, source.data());

  sourceChar[source.size()] = '\0';

  return sourceChar;
}

bool OpenGLShader::VerifyShaderCompilation(std::string errorMessage) const
{
  // check if vertex shader compiled correctly
  int success;
  char infoLog[512] = { '\0' };
  glGetShaderiv(mShader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(mShader, 512, nullptr, infoLog);
    std::string error = errorMessage + ": " + std::string(infoLog);
    throw error;
    return false;
  }

  return true;
}

} // End of Elba namespace
