#include "Elba/Graphics/OpenGL/Pipeline/OpenGLComputeShader.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLPostProcess.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

#include "Elba/Utilities/Utils.hpp"

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

  // create empty second texture to write to
  mTextures[0] = CreateTexture(0);
  
  // initialize first texture with texture from framebuffer
  OpenGLFramebuffer* framebuffer = mGraphics->GetFramebuffer();
  mTextures[1].id = framebuffer->GetTexture();
  mTextures[1].width = dim.first;
  mTextures[1].height = dim.second;
  mTextures[1].slot = 1;
}

GlobalKey OpenGLPostProcess::AddComputeShader(std::string filename)
{
  // add the asset path to the given file path
  std::string fullPath = Utils::GetAssetsDirectory() + "Shaders/" + filename;

  UniquePtr<OpenGLProgram> program = NewUnique<OpenGLProgram>("compute");

  UniquePtr<OpenGLComputeShader> shader = NewUnique<OpenGLComputeShader>(mGraphics, fullPath);

  GlobalKey shaderKey = program->AttachShader(std::move(shader));

  program->Link();

  program->Use();

  mComputeShaders.push_back(std::make_pair(shaderKey.ToStdString(), std::move(program)));

  return shaderKey;
}

void OpenGLPostProcess::DispatchComputeShaders()
{
  // start with the texture ptrs flipped, so after the first swap they will be correct
  PostProcessTexture* input =  &mTextures[0];
  PostProcessTexture* output = &mTextures[1];

  for (auto& pair : mComputeShaders)
  {
    std::swap(input, output);

    pair.second->Use();
    OpenGLComputeShader* shader = static_cast<OpenGLComputeShader*>(pair.second->GetShader(pair.first));
    shader->SetOutputTexture(output);
    shader->SetInputTexture(input);
    shader->BindTextures(pair.second.get());
    shader->Dispatch();

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    shader->UnbindTextures();
  }

  mFinalTexture = output;
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

  glBindImageTexture(0, texture.id, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

  return texture;
}

} // End of Elba namespace
