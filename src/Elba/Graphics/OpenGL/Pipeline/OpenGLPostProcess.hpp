#pragma once

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLComputeShader.hpp"

#include "Elba/Utilities/GlobalKey.hpp"
#include "Elba/Utilities/StdTypedefs.hpp"


namespace Elba
{
class OpenGLModule;

struct PostProcessTexture
{
  GLuint id;
  GLuint width;
  GLuint height;
  GLuint slot;
};

class OpenGLPostProcess
{
public:
  OpenGLPostProcess(OpenGLModule* module);

  GlobalKey AddComputeShader(std::string path);

  void DispatchComputeShaders();

private:
  OpenGLModule* mGraphics;

  Map<std::string, UniquePtr<OpenGLComputeShader> > mComputeShaders;

  PostProcessTexture mTextures[2];

  PostProcessTexture CreateTexture(int slot);

};

} // End of Elba namespace

