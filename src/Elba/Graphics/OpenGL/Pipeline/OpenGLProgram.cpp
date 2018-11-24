/**
* \file OpenGLProgram.cpp
* \author Nicholas Ammann
* \date 10/9/2018
* \brief Base class for handling glProgram.
*/

#include <fstream>

#include <gl/glew.h>

#include <glm/gtc/type_ptr.hpp>

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLShader.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLProgram.hpp"

namespace Elba
{
OpenGLProgram::OpenGLProgram(const char* aName)
  : mName(aName)
  , mProgram(0)
{
  mProgram = glCreateProgram();
}

void OpenGLProgram::Use()
{
  glUseProgram(mProgram);
}

void OpenGLProgram::Link()
{
  glLinkProgram(mProgram);

  int success;
  char infoLog[512] = { '\0' };

  // check if linking the shader program was succesful
  glGetProgramiv(mProgram, GL_LINK_STATUS, &success);

  if (!success)
  {
    glGetProgramInfoLog(mProgram, 512, nullptr, infoLog);

    std::string log = infoLog;
    std::string error = std::string(mName) + ": (Program failed to link) : " + log;
    throw error;
  }
}

void OpenGLProgram::SetUniform(const std::string& name, bool value)
{
  glUniform1i(glGetUniformLocation(mProgram, name.c_str()), static_cast<int>(value));
}

void OpenGLProgram::SetUniform(const std::string& name, int value)
{
  glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
}

void OpenGLProgram::SetUniform(const std::string& name, float value)
{
  glUniform1f(glGetUniformLocation(mProgram, name.c_str()), value);
}

void OpenGLProgram::SetUniform(const std::string& name, glm::vec3 value)
{
  glUniform3f(glGetUniformLocation(mProgram, name.c_str()), value.x, value.y, value.z);
}

void OpenGLProgram::SetUniform(const std::string& name, glm::mat4x4 value)
{
  GLuint loc = glGetUniformLocation(mProgram, name.c_str());
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLProgram::SetUniform(const OpenGLUniformInt& uniform)
{
  mUniformInts[uniform.name] = uniform;
}

void OpenGLProgram::SetUniform(const OpenGLUniformFloat& uniform)
{
  mUniformFloats[uniform.name] = uniform;
}

void OpenGLProgram::SetUniform(const OpenGLUniformMat4& uniform)
{
  mUniformMat4s[uniform.name] = uniform;
}

void OpenGLProgram::BindUniforms()
{
  for (auto pair : mUniformInts)
  {
    SetUniform(pair.second.name, pair.second.value);
  }

  for (auto pair : mUniformFloats)
  {
    SetUniform(pair.second.name, pair.second.value);
  }

  for (auto pair : mUniformMat4s)
  {
    SetUniform(pair.second.name, pair.second.value);
  }
}

unsigned int OpenGLProgram::Get() const
{
  return mProgram;
}

std::string OpenGLProgram::GetName()
{
  return mName;
}

GlobalKey OpenGLProgram::AttachShader(UniquePtr<OpenGLShader> shader)
{
  // attach new shader to program
  glAttachShader(mProgram, shader->GetShaderId());

  // generate new key
  GlobalKey key;

  // store shader
  mShaders.emplace(key.ToStdString(), std::move(shader));

  return key;
}

OpenGLShader* OpenGLProgram::GetShader(std::string key)
{
  auto it = mShaders.find(key);

  if (it != mShaders.end())
  {
    return it->second.get();
  }

  return nullptr;
}

OpenGLUniformInt::OpenGLUniformInt(std::string n, int v)
  : name(n)
  , value(v)
{
}

OpenGLUniformFloat::OpenGLUniformFloat(std::string n, float v)
  : name(n)
  , value(v)
{
}

OpenGLUniformMat4::OpenGLUniformMat4(std::string n, glm::mat4x4 v)
  : name(n)
  , value(v)
{
}

} // End of Elba namespace
