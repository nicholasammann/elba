#include "Elba/Graphics/OpenGL/OpenGLComputeShader.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

namespace Elba
{

OpenGLComputeShader::OpenGLComputeShader(OpenGLModule* module)
  : mGraphics(module)
{
}

void OpenGLComputeShader::LoadShader(std::string name)
{

}

void OpenGLComputeShader::GenerateOutputTexture()
{
  std::pair<int, int> dim = mGraphics->GetScreenDimensions();

  glGenTextures(1, &mOutputTexture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mOutputTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, dim.first, dim.second,
               0, GL_RGBA, GL_FLOAT, nullptr);

  glBindImageTexture(0, mOutputTexture, 0, GL_FALSE, 0,
                     GL_WRITE_ONLY, GL_RGBA32F);
}

} // End of Elba namespace
