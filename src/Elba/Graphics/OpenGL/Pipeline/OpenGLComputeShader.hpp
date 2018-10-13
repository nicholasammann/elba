#pragma once

#include <string>

#include <gl/glew.h>

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLProgram.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLShader.hpp"

namespace Elba
{
class OpenGLModule;
struct PostProcessTexture;

class OpenGLComputeShader : public OpenGLShader
{
public:
  OpenGLComputeShader(OpenGLModule* module, std::string path, OpenGLProgram* program);

  void Dispatch();

  void BindTextures();
  void UnbindTextures();

  void SetInputTexture(PostProcessTexture* texture);
  void SetOutputTexture(PostProcessTexture* texture);

private:
  OpenGLModule* mGraphics;
  OpenGLProgram* mProgram;
  PostProcessTexture* mInputTexture;
  PostProcessTexture* mOutputTexture;
};

} // End of Elba namespace
