#pragma once

#include <string>

#include <gl/glew.h>

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLShader.hpp"

namespace Elba
{

class OpenGLModule;

struct ComputeShaderTexture
{
  GLuint id;
  GLuint width;
  GLuint height;
};

class OpenGLComputeShader : public OpenGLShader
{
public:
  OpenGLComputeShader(OpenGLModule* module, std::string path);

  void Dispatch();

private:

  void GenerateOutputTexture();

  OpenGLModule* mGraphics;

  GLuint mProgram;

  ComputeShaderTexture mOutputTexture;
};

} // End of Elba namespace
