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

namespace Elba
{
class OpenGLShader;

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

  void Link();

  // utility uniform functions
  void SetUniform(const std::string& name, bool value);
  void SetUniform(const std::string& name, int value);
  void SetUniform(const std::string& name, float value);
  void SetUniform(const std::string& name, glm::mat4x4 value);

  unsigned int Get() const;

  std::string GetName();

  GlobalKey AttachShader(UniquePtr<OpenGLShader> shader);

protected:
  Map<std::string, UniquePtr<OpenGLShader> > mShaders;

private:
  std::string mName;
  unsigned int mProgram;
};

} // End of Elba namespace
