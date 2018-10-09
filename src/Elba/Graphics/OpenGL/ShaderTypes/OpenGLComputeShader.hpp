#pragma once

#include <string>

#include <gl/glew.h>

namespace Elba
{

class OpenGLModule;

class OpenGLComputeShader
{
public:
  OpenGLComputeShader(OpenGLModule* module);

  void LoadShader(std::string name);

private:

  void GenerateOutputTexture();

  OpenGLModule* mGraphics;

  GLuint mProgram;

  GLuint mShader;
  std::string mShaderSource;

  GLuint mOutputTexture;

};

} // End of Elba namespace
