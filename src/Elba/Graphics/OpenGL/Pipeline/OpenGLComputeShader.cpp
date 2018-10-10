#include "Elba/Graphics/OpenGL/Pipeline/OpenGLComputeShader.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

namespace Elba
{

OpenGLComputeShader::OpenGLComputeShader(OpenGLModule* module, std::string path)
  : OpenGLShader(path)
  , mGraphics(module)
{
  mShader = glCreateShader(GL_COMPUTE_SHADER);
  glShaderSource(mShader, 1, &mShaderSource, nullptr);
  glCompileShader(mShader);

  VerifyShaderCompilation("Compute shader failed to compile");

  mProgram = glCreateProgram();
  glAttachShader(mProgram, mShader);
  glLinkProgram(mProgram);
}

void OpenGLComputeShader::Dispatch()
{
  glUseProgram(mProgram);
  glDispatchCompute(mOutputTexture.width, mOutputTexture.height, 1);
}

void OpenGLComputeShader::GenerateOutputTexture()
{
  std::pair<int, int> dim = mGraphics->GetScreenDimensions();
  mOutputTexture.width = dim.first;
  mOutputTexture.height = dim.second;

  glGenTextures(1, &mOutputTexture.id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mOutputTexture.id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, mOutputTexture.width, mOutputTexture.height,
               0, GL_RGBA, GL_FLOAT, nullptr);

  glBindImageTexture(0, mOutputTexture.id, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
}

} // End of Elba namespace
