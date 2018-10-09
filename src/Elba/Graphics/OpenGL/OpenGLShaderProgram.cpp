/**
* \file Shader.cpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Member function definitions for Shader.
*/

#include <fstream>

#include <gl/glew.h>

#include "Elba/Graphics/OpenGL/OpenGLShaderProgram.hpp"

namespace Elba
{
OpenGLShaderProgram::OpenGLShaderProgram(const char* aName, const char* vertPath, const char* fragPath)
: mName(aName), mShaderProgram(0), mVertShader(0), mFragShader(0),
mVertPath(vertPath), mFragPath(fragPath)
{
  // read in vertex shader
  const GLchar* vertexShaderSource = ReadShader(vertPath);

  // create a shader object (return value is the id)
  mVertShader = glCreateShader(GL_VERTEX_SHADER);

  // attach vertex shader source code
  glShaderSource(mVertShader, 1, &vertexShaderSource, nullptr);

  // compile vertex shader
  glCompileShader(mVertShader);

  // check if vertex shader compiled correctly
  int success;
  char infoLog[512] = { '\0' };
  glGetShaderiv(mVertShader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(mVertShader, 512, nullptr, infoLog);
    std::string error = std::string(vertPath) + " : (Vertex Shader compilation failed) : " + std::string(infoLog);
    throw error;
  }

  // read in fragment shader
  const GLchar *fragmentShaderSource = ReadShader(fragPath);

  // create a shader object
  mFragShader = glCreateShader(GL_FRAGMENT_SHADER);

  // attach fragment shader source code
  glShaderSource(mFragShader, 1, &fragmentShaderSource, nullptr);

  // compile fragment shader
  glCompileShader(mFragShader);

  // check if fragment shader compiled correctly
  glGetShaderiv(mFragShader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(mFragShader, 512, nullptr, infoLog);
    std::string error = std::string(fragPath) + " : (Fragment Shader compilation failed) : " + std::string(infoLog);
    throw error;
  }

  // create a shader program
  mShaderProgram = glCreateProgram();

  // attach shaders and link program
  glAttachShader(mShaderProgram, mVertShader);
  glAttachShader(mShaderProgram, mFragShader);
  glLinkProgram(mShaderProgram);

  try
  {
    // check if linking the shader program was succesful
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
  }
  catch (...)
  {
  }

  if (!success)
  {
    glGetProgramInfoLog(mShaderProgram, 512, nullptr, infoLog);

    std::string log = infoLog;
    std::string error = std::string(aName) + ": (Shader Program failed to link) : " + log;
    throw error;
  }

  glUseProgram(mShaderProgram);

  // delete the shader objects (we don't need them anymore)
  //glDeleteShader(mVertShader);
  //glDeleteShader(mFragShader);
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

unsigned int OpenGLShaderProgram::GetVertShader() const
{
  return mVertShader;
}

unsigned int OpenGLShaderProgram::GetFragShader() const
{
  return mFragShader;
}

std::string OpenGLShaderProgram::GetName()
{
  return mName;
}

std::string OpenGLShaderProgram::GetVertPath()
{
  return mVertPath;
}

std::string OpenGLShaderProgram::GetFragPath()
{
  return mFragPath;
}

} // End of Elba namespace
