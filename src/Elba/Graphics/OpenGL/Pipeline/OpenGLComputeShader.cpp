#include "Elba/Graphics/OpenGL/Pipeline/OpenGLComputeShader.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLPostProcess.hpp"
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
}

void OpenGLComputeShader::Dispatch()
{
  glDispatchCompute(mInputTexture->width, mInputTexture->height, 1);
}

void OpenGLComputeShader::BindTextures(OpenGLProgram* program)
{
  program->SetUniform("img_input", 0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mInputTexture->id);
 
  program->SetUniform("img_output", 1);
  glActiveTexture(GL_TEXTURE0 + 1);
  glBindTexture(GL_TEXTURE_2D, mOutputTexture->id);
}

void OpenGLComputeShader::UnbindTextures()
{
  // input texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);

  // output texture
  glActiveTexture(GL_TEXTURE0 + 1);
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

PostProcessTexture* OpenGLComputeShader::GetInputTexture()
{
  return mInputTexture;
}

PostProcessTexture* OpenGLComputeShader::GetOutputTexture()
{
  return mOutputTexture;
}

} // End of Elba namespace
