#pragma once

#include "Elba/Graphics/GraphicsModule.hpp"
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

  GlobalKey AddComputeShader(std::string filename);

  void DispatchComputeShaders();

  PostProcessTexture* GetOutputTexture();

private:
  OpenGLModule* mGraphics;

  Vector<std::pair<std::string, UniquePtr<OpenGLProgram> > > mComputeShaders;

  PostProcessTexture mTextures[2];

  PostProcessTexture CreateTexture(int slot);

  PostProcessTexture* mFinalTexture;

  void OnResize(const ResizeEvent& event);

};

} // End of Elba namespace

