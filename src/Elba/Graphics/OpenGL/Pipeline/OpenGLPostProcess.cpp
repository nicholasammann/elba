#include "Elba/Graphics/OpenGL/Pipeline/OpenGLComputeShader.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLPostProcess.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

namespace Elba
{

OpenGLPostProcess::OpenGLPostProcess(OpenGLModule* module)
  : mGraphics(module)
  , mFinalTexture(nullptr)
{
}

void OpenGLPostProcess::Initialize()
{
  std::pair<int, int> dim = mGraphics->GetScreenDimensions();

  // initialize first texture with texture from framebuffer
  OpenGLFramebuffer* framebuffer = mGraphics->GetFramebuffer();
  mTextures[0].id = framebuffer->GetTexture();
  mTextures[0].width = dim.first;
  mTextures[0].height = dim.second;
  mTextures[0].slot = 0;

  // create empty second texture to write to
  mTextures[1] = CreateTexture(1);
}

GlobalKey OpenGLPostProcess::AddComputeShader(std::string path)
{
  UniquePtr<OpenGLProgram> program = NewUnique<OpenGLProgram>("compute");
  program->Use();

  UniquePtr<OpenGLComputeShader> shader = NewUnique<OpenGLComputeShader>(mGraphics, path, program.get());

  GlobalKey shaderKey = program->AttachShader(std::move(shader));
  
  program->Link();

  mComputeShaders.push_back(std::make_pair(shaderKey.ToStdString(), std::move(program)));

  return shaderKey;
}

void OpenGLPostProcess::DispatchComputeShaders()
{
  PostProcessTexture* input = &mTextures[0];
  PostProcessTexture* output = &mTextures[1];

  for (auto& pair : mComputeShaders)
  {
    pair.second->Use();
    OpenGLComputeShader* shader = static_cast<OpenGLComputeShader*>(pair.second->GetShader(pair.first));
    shader->SetInputTexture(input);
    shader->SetOutputTexture(output);
    shader->BindTextures();
    shader->Dispatch();

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    std::swap(input, output);
  }

  mFinalTexture = input;
}

PostProcessTexture* OpenGLPostProcess::GetOutputTexture()
{
  return mFinalTexture;
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
