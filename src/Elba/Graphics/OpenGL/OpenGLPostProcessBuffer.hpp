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

  void Bind();
  void Unbind();

  void Draw();

  void LoadShader(std::string shaderName);

private:
  OpenGLModule* mGraphicsModule;

  // buffers
  GLuint mMSFbo;
  GLuint mFbo;
  GLuint mRbo;

  GLuint mFboTexture;
  GLuint mFboTextureSlot;
  GLuint mFboVertices;

  //GLuint mProgram;
  GLuint mAttributeVcoord;
  GLuint mUniformFboTexture;

  void OnResize(const ResizeEvent& event);

  OpenGLShader* mShader;
  OpenGLTexture* mTexture;

  int mWidth;
  int mHeight;

  GLuint mVAO;
};

} // End of Elba namespace

