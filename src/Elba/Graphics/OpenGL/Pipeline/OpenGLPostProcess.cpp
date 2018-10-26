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
  // create texture to copy framebuffer output into
  mTextures[0] = CreateTexture(0);

  // create empty second texture to write to
  mTextures[1] = CreateTexture(1);

  mGraphics->RegisterForResize(GlobalKey(), [this](const ResizeEvent& event) { this->OnResize(event); });
}

GlobalKey OpenGLPostProcess::AddComputeShader(std::string filename)
{
  // add the asset path to the given file path
  std::string fullPath = Utils::GetAssetsDirectory() + "Shaders/Compute/" + filename;

  UniquePtr<OpenGLProgram> program = NewUnique<OpenGLProgram>("compute");

  UniquePtr<OpenGLComputeShader> shader = NewUnique<OpenGLComputeShader>(mGraphics, fullPath);

  GlobalKey shaderKey = program->AttachShader(std::move(shader));

  program->Link();

  mComputeShaders.push_back(std::make_pair(shaderKey.ToStdString(), std::move(program)));

  return shaderKey;
}

void OpenGLPostProcess::DispatchComputeShaders()
{
  std::pair<int, int> dim = mGraphics->GetScreenDimensions();
  OpenGLFramebuffer* framebuffer = mGraphics->GetFramebuffer();
  glCopyImageSubData(framebuffer->GetTexture(), GL_TEXTURE_2D, 0, 0, 0, 0,
                     mTextures[0].id, GL_TEXTURE_2D, 0, 0, 0, 0, 
                     dim.first, dim.second, 1);

  // start with the texture ptrs flipped, so after the first swap they will be correct
  PostProcessTexture* output = &mTextures[0];
  PostProcessTexture* input =  &mTextures[1];

  for (auto& pair : mComputeShaders)
  {
    std::swap(output, input);
    pair.second->Use();
    OpenGLComputeShader* shader = static_cast<OpenGLComputeShader*>(pair.second->GetShader(pair.first));
    shader->SetOutputTexture(output);
    shader->SetInputTexture(input);
    shader->BindTextures(pair.second.get());
    pair.second->BindUniforms();
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

OpenGLProgram* OpenGLPostProcess::GetComputeProgram(const GlobalKey& key)
{
  auto res = std::find_if(
    mComputeShaders.begin(),
    mComputeShaders.end(), 
    [key](const std::pair<std::string, Elba::UniquePtr<OpenGLProgram> >& item) {
      return key.ToStdString() == item.first;
    }
  );

  if (res != mComputeShaders.end())
  {
    return res->second.get();
  }
  return nullptr;
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

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, texture.width, texture.height, 0, GL_RGBA, GL_FLOAT, nullptr);

  glBindImageTexture(slot, texture.id, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

  return texture;
}

void OpenGLPostProcess::OnResize(const ResizeEvent& event)
{
  GLuint w = static_cast<GLuint>(event.newSize.x);
  GLuint h = static_cast<GLuint>(event.newSize.y);

  // resize textures
  for (int i = 0; i < 2; ++i)
  {
    mTextures[i].width = w;
    mTextures[i].height = h;

    glActiveTexture(GL_TEXTURE0 + mTextures[i].slot);
    glBindTexture(GL_TEXTURE_2D, mTextures[i].id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, w, h, 0, GL_RGBA, GL_FLOAT, nullptr);

    glBindImageTexture(mTextures[i].slot, mTextures[i].id, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
  }
}

} // End of Elba namespace
