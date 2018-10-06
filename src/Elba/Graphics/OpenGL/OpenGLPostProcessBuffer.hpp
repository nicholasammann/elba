#pragma once

#include <gl/glew.h>

#include "Elba/Graphics/GraphicsModule.hpp"

namespace Elba
{
class OpenGLModule;
class OpenGLShader;
class OpenGLTexture;

class OpenGLPostProcessBuffer
{
public:
  OpenGLPostProcessBuffer(OpenGLModule* graphicsModule);
  ~OpenGLPostProcessBuffer();

  void InitializeBuffers(int textureSlot);
  void InitializeQuad();
  void InitializeProgram();

  void PreRender();
  void PostRender();

  void Draw();

  void LoadShader(std::string shaderName);

private:
  OpenGLModule* mGraphicsModule;

  // buffers
  GLuint mFbo;
  GLuint mRbo;
  GLuint mVAO;

  GLuint mTextureColorBuffer;

  //GLuint mProgram;
  GLuint mUniformFboTexture;

  void OnResize(const ResizeEvent& event);

  OpenGLShader* mShader;

  int mWidth;
  int mHeight;

  float mElapsedTime;

};

} // End of Elba namespace

