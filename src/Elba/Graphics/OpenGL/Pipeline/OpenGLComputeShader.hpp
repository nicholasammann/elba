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
  OpenGLComputeShader(OpenGLModule* module, std::string path);

  void Dispatch();

  void BindTextures(OpenGLProgram* program);
  void UnbindTextures();

  void SetInputTexture(PostProcessTexture* texture);
  void SetOutputTexture(PostProcessTexture* texture);

  PostProcessTexture* GetInputTexture();
  PostProcessTexture* GetOutputTexture();

private:
  OpenGLModule* mGraphics;
  PostProcessTexture* mInputTexture;
  PostProcessTexture* mOutputTexture;
};

} // End of Elba namespace
