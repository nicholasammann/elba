/**
* \file Shader.hpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Class definition for Shader.
*/

#include <string>

namespace Elba
{
/**
* \brief Contains vertex and fragment shader information
*/
class OpenGLShader
{
public:
  /** 
  * \brief Constructor
  * \param name The arbitrary name we give this shader set.
  * \param vertPath The path to the vertex shader.
  * \param fragPath The path to the fragment shader.
  */
  OpenGLShader(const char* name, const char* vertPath, const char* fragPath);

  /**
  * \brief Set this as the currently active shader for OpenGL
  */
  void UseShaderProgram();

  // utility uniform functions
  void SetBool(const std::string& name, bool value);
  void SetInt(const std::string& name, int value);
  void SetFloat(const std::string& name, float value);

  unsigned int GetShaderProgram() const;
  unsigned int GetVertShader() const;
  unsigned int GetFragShader() const;

  std::string GetName();
  std::string GetVertPath();
  std::string GetFragPath();

private:
  std::string mName;
  std::string mVertPath;
  std::string mFragPath;

  unsigned int mShaderProgram;
  unsigned int mVertShader;
  unsigned int mFragShader;

  // reads in a shader from file
  const GLchar* ReadShader(const std::string& filename);
};

} // End of Elba namespace
