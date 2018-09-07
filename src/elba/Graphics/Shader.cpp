/**
* \file Shader.cpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Member function definitions for Shader.
*/

#include "Graphics/Shader.hpp"

namespace Elba
{
/*
  Shader::Shader(const char *aName, const char *vertPath, const char *fragPath)
  : mName(aName), mShaderProgram(0), mVertShader(0), mFragShader(0),
    mVertPath(vertPath), mFragPath(fragPath)
{
  // read in vertex shader
  const GLchar *vertexShaderSource = ReadShader(vertPath);

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
    std::cout << "Exception" << std::endl;
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

void Shader::UseShaderProgram()
{
  glUseProgram(mShaderProgram);
}

void Shader::SetBool(const std::string &name, bool value)
{
  glUniform1i(glGetUniformLocation(mShaderProgram, name.c_str()), static_cast<int>(value));
}

void Shader::SetInt(const std::string &name, int value)
{
  glUniform1i(glGetUniformLocation(mShaderProgram, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value)
{
  glUniform1f(glGetUniformLocation(mShaderProgram, name.c_str()), value);
}

unsigned int Shader::GetShaderProgram() const
{
  return mShaderProgram;
}

unsigned int Shader::GetVertShader() const
{
  return mVertShader;
}

unsigned int Shader::GetFragShader() const
{
  return mFragShader;
}

std::string Shader::GetName()
{
  return mName;
}

std::string Shader::GetVertPath()
{
  return mVertPath;
}

std::string Shader::GetFragPath()
{
  return mFragPath;
}

const GLchar * Shader::ReadShader(const std::string & filename)
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
    std::cout << "Unable to open shader: " + filename << std::endl;
  }

  char *sourceChar = new char[source.size() + 1];
  strcpy(sourceChar, source.data());

  sourceChar[source.size()] = '\0';

  return sourceChar;
}
*/

} // End of Elba namespace
