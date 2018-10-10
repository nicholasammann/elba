#pragma once

#include <gl/glew.h>

#include "Elba/Graphics/GraphicsModule.hpp"

namespace Elba
{
class OpenGLModule;
class OpenGLProgram;
class OpenGLTexture;

class OpenGLFramebuffer
{
public:
  OpenGLFramebuffer(OpenGLModule* graphicsModule);
  ~OpenGLFramebuffer();

  void InitializeBuffers(int textureSlot);
  void InitializeQuad();
  void InitializeProgram();

  void PreRender();
  void PostRender();

  void Draw();

  void LoadShaders(std::string shaderName);

  void SetEdgeDetection(int value);
  void SetBlur(int value);

  GLuint GetTexture() const;

private:
  OpenGLModule* mGraphicsModule;

  // buffers
  GLuint mFbo;
  GLuint mRbo;
  GLuint mVAO;

  GLuint mTextureColorBuffer;

  void OnResize(const ResizeEvent& event);

  OpenGLProgram* mProgram;

  int mWidth;
  int mHeight;

  float mElapsedTime;

  // Options (temp solution)
  int mEdgeDetectionOn;
  int mBlurOn;

};

} // End of Elba namespace

