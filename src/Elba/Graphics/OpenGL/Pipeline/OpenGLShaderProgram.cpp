/**
* \file Shader.cpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Member function definitions for Shader.
*/

#include <fstream>

#include <gl/glew.h>

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLShaderProgram.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLVertexShader.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLFragmentShader.hpp"

namespace Elba
{
OpenGLShaderProgram::OpenGLShaderProgram(const char* aName, const char* vertPath, const char* fragPath)
  : mName(aName)
  , mShaderProgram(0)
{
  mVertShader = new OpenGLVertexShader(vertPath);
  mFragShader = new OpenGLFragmentShader(fragPath);

  // create a shader program
  mShaderProgram = glCreateProgram();

  // attach shaders and link program
  glAttachShader(mShaderProgram, mVertShader->GetShaderId());
  glAttachShader(mShaderProgram, mFragShader->GetShaderId());
  glLinkProgram(mShaderProgram);

  int success;
  char infoLog[512] = { '\0' };
  
  // check if linking the shader program was succesful
  glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
  
  if (!success)
  {
    glGetProgramInfoLog(mShaderProgram, 512, nullptr, infoLog);

    std::string log = infoLog;
    std::string error = std::string(aName) + ": (Shader Program failed to link) : " + log;
    throw error;
  }

  glUseProgram(mShaderProgram);
}

void OpenGLShaderProgram::UseShaderProgram()
{
  glUseProgram(mShaderProgram);
}

void OpenGLShaderProgram::SetBool(const std::string& name, bool value)
{
  glUniform1i(glGetUniformLocation(mShaderProgram, name.c_str()), static_cast<int>(value));
}

void OpenGLShaderProgram::SetInt(const std::string& name, int value)
{
  glUniform1i(glGetUniformLocation(mShaderProgram, name.c_str()), value);
}

void OpenGLShaderProgram::SetFloat(const std::string& name, float value)
{
  glUniform1f(glGetUniformLocation(mShaderProgram, name.c_str()), value);
}

unsigned int OpenGLShaderProgram::GetShaderProgram() const
{
  return mShaderProgram;
}

std::string OpenGLShaderProgram::GetName()
{
  return mName;
}

} // End of Elba namespace
