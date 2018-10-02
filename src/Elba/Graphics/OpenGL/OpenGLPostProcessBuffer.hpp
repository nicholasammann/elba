#pragma once

#include <gl/glew.h>

#include "Elba/Graphics/GraphicsModule.hpp"

namespace Elba
{
class OpenGLModule;
class OpenGLShader;

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
  GLuint mFbo;
  GLuint mFboTexture;
  GLuint mFboTextureSlot;
  GLuint mFboVertices;
  GLuint mRboDepth;

  GLuint mProgram;
  GLuint mAttributeVcoord;
  GLuint mUniformFboTexture;

  void OnResize(const ResizeEvent& event);

  OpenGLShader* mShader;
};

} // End of Elba namespace

