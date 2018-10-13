#include "Elba/Graphics/OpenGL/Pipeline/OpenGLComputeShader.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLPostProcess.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

namespace Elba
{

OpenGLComputeShader::OpenGLComputeShader(OpenGLModule* module, std::string path, OpenGLProgram* program)
  : OpenGLShader(path)
  , mGraphics(module)
  , mProgram(program)
{
  mShader = glCreateShader(GL_COMPUTE_SHADER);
  glShaderSource(mShader, 1, &mShaderSource, nullptr);
  glCompileShader(mShader);

  VerifyShaderCompilation("Compute shader failed to compile");
}

void OpenGLComputeShader::Dispatch()
{
  glDispatchCompute(mInputTexture->width, mInputTexture->height, 1);
}

void OpenGLComputeShader::BindTextures()
{
  glActiveTexture(GL_TEXTURE0 + mOutputTexture->slot);
  glBindTexture(GL_TEXTURE_2D, mOutputTexture->id);

  glActiveTexture(GL_TEXTURE0 + mInputTexture->slot);
  glBindTexture(GL_TEXTURE_2D, mInputTexture->id);
}

void OpenGLComputeShader::UnbindTextures()
{
  // output texture
  glActiveTexture(GL_TEXTURE0 + mOutputTexture->slot);
  glBindTexture(GL_TEXTURE_2D, 0);

  // input texture
  glActiveTexture(GL_TEXTURE0 + mInputTexture->slot);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLComputeShader::SetInputTexture(PostProcessTexture* texture)
{
  mInputTexture = texture;
}

void OpenGLComputeShader::SetOutputTexture(PostProcessTexture* texture)
{
  mOutputTexture = texture;
}

} // End of Elba namespace
