/**
* \file OpenGLProgram.hpp
* \author Nicholas Ammann
* \date 10/9/2018
* \brief Base class for handling glProgram.
*/

#pragma once

#include <string>

#include <gl/glew.h>
#include <glm/mat4x4.hpp>

#include "Elba/Utilities/GlobalKey.hpp"
#include "Elba/Utilities/StdTypedefs.hpp"

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLShader.hpp"

namespace Elba
{

struct OpenGLUniformInt
{
  OpenGLUniformInt(std::string n = "", int v = 0);
  std::string name;
  int value;
};

struct OpenGLUniformFloat
{
  OpenGLUniformFloat(std::string n = "", float v = 0.0f);
  std::string name;
  float value;
};

struct OpenGLUniformMat4
{
  OpenGLUniformMat4(std::string n = "", glm::mat4x4 v = glm::mat4x4());
  std::string name;
  glm::mat4x4 value;
};

/**
* \brief Contains vertex and fragment shader information
*/
class OpenGLProgram
{
public:
  /**
  * \brief Constructor
  * \param name The arbitrary name we give this shader set.
  * \param vertPath The path to the vertex shader.
  * \param fragPath The path to the fragment shader.
  */
  OpenGLProgram(const char* name);

  /**
  * \brief Set this as the currently active shader for OpenGL
  */
  void Use();

  unsigned int Get() const;

  void Link();

  // utility uniform functions
  void SetUniform(const std::string& name, bool value);
  void SetUniform(const std::string& name, int value);
  void SetUniform(const std::string& name, float value);
  void SetUniform(const std::string& name, glm::mat4x4 value);

  void SetUniform(const OpenGLUniformInt& uniform);
  void SetUniform(const OpenGLUniformFloat& uniform);
  void SetUniform(const OpenGLUniformMat4& uniform);

  void BindUniforms();

  std::string GetName();

  GlobalKey AttachShader(UniquePtr<OpenGLShader> shader);

  OpenGLShader* GetShader(std::string key);

protected:
  Map<std::string, UniquePtr<OpenGLShader> > mShaders;
  Map<std::string, OpenGLUniformInt> mUniformInts;
  Map<std::string, OpenGLUniformFloat> mUniformFloats;
  Map<std::string, OpenGLUniformMat4> mUniformMat4s;

private:
  std::string mName;
  unsigned int mProgram;
};

} // End of Elba namespace
