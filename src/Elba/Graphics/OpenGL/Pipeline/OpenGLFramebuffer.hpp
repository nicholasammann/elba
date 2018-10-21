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

  GLuint GetTexture() const;
  void SetTexture(GLuint texId);

  void SetDoImageNegative(int value);
  void SetDoLogTransform(int value);
  void SetDoGammaTransform(int value);
  void SetDoEdgeDetection(int value);
  void SetValueC(float value);
  void SetValueGamma(float value);

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

  // Possible post processing features
  int mDoImageNegative;

  int mDoLogTransform;
  
  int mDoGammaTransform;
  float mValueC;
  float mValueGamma;

  int mDoEdgeDetection;
};

} // End of Elba namespace

