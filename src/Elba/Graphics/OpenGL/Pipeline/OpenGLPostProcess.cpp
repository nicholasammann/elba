#include "Elba/Graphics/OpenGL/Pipeline/OpenGLPostProcess.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

namespace Elba
{

OpenGLPostProcess::OpenGLPostProcess(OpenGLModule* module)
  : mGraphics(module)
{
  mTextures[0] = CreateTexture(0);
  mTextures[1] = CreateTexture(1);
}

GlobalKey OpenGLPostProcess::AddComputeShader(std::string path)
{
  UniquePtr<OpenGLComputeShader> shader = NewUnique<OpenGLComputeShader>(this, path);

  GlobalKey key;
  mComputeShaders.emplace(key.ToStdString(), std::move(shader));

  return key;
}

void OpenGLPostProcess::DispatchComputeShaders()
{
}

PostProcessTexture OpenGLPostProcess::CreateTexture(int slot)
{
  PostProcessTexture texture;
  texture.slot = slot;

  std::pair<int, int> dim = mGraphics->GetScreenDimensions();
  texture.width = dim.first;
  texture.height = dim.second;

  glGenTextures(1, &texture.id);
  glActiveTexture(GL_TEXTURE0 + texture.slot);
  glBindTexture(GL_TEXTURE_2D, texture.id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, texture.width, texture.height,
    0, GL_RGBA, GL_FLOAT, nullptr);

  glBindImageTexture(0, texture.id, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

  return texture;
}

} // End of Elba namespace
