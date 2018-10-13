#pragma once

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLProgram.hpp"

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

  void Initialize();

  GlobalKey AddComputeShader(std::string path);

  void DispatchComputeShaders();

  PostProcessTexture* GetOutputTexture();

private:
  OpenGLModule* mGraphics;

  Vector<std::pair<std::string, UniquePtr<OpenGLProgram> > > mComputeShaders;

  PostProcessTexture mTextures[2];

  PostProcessTexture CreateTexture(int slot);

  PostProcessTexture* mFinalTexture;

};

} // End of Elba namespace

