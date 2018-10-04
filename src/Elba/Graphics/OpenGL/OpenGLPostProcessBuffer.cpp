#include <iostream>

#include "Elba/Engine.hpp"
#include "Elba/Graphics/OpenGL/OpenGLPostProcessBuffer.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLShader.hpp"
#include "Elba/Utilities/Utils.hpp"

namespace Elba
{
OpenGLPostProcessBuffer::OpenGLPostProcessBuffer(OpenGLModule* graphicsModule)
  : mGraphicsModule(graphicsModule)
  , mShader(nullptr)
{
}

OpenGLPostProcessBuffer::~OpenGLPostProcessBuffer()
{
  glDeleteRenderbuffers(1, &mRboDepth);
  glDeleteTextures(1, &mFboTexture);
  glDeleteFramebuffers(1, &mFbo);
  glDeleteBuffers(1, &mFboVertices);
  glDeleteProgram(mProgram);
}

void OpenGLPostProcessBuffer::InitializeBuffers(int textureSlot)
{
  // width, height
  std::pair<int, int> screenSize = mGraphicsModule->GetScreenDimensions();

  mFboTextureSlot = textureSlot;

  // Texture
  glActiveTexture(GL_TEXTURE0 + textureSlot);

  GLenum error = glGetError();
  auto errStr = glewGetErrorString(error);

  glGenTextures(1, &mFboTexture);
  
  error = glGetError();
  errStr = glewGetErrorString(error);
  
  glBindTexture(GL_TEXTURE_2D, mFboTexture);

  error = glGetError();
  errStr = glewGetErrorString(error);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  
  error = glGetError();
  errStr = glewGetErrorString(error);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

  error = glGetError();
  errStr = glewGetErrorString(error);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenSize.first, screenSize.second,
               0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  error = glGetError();
  errStr = glewGetErrorString(error);

  glBindTexture(GL_TEXTURE_2D, 0);

  error = glGetError();
  errStr = glewGetErrorString(error);

  // Depth buffer
  glGenRenderbuffers(1, &mRboDepth);
  glBindRenderbuffer(GL_RENDERBUFFER, mRboDepth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 
                        screenSize.first, screenSize.second);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  // Framebuffer to link everything together
  glGenFramebuffers(1, &mFbo);
  glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                         GL_TEXTURE_2D, mFboTexture, 0);

  error = glGetError();
  errStr = glewGetErrorString(error);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
                            GL_RENDERBUFFER, mRboDepth);

  error = glGetError();
  errStr = glewGetErrorString(error);

  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

  if (status != GL_FRAMEBUFFER_COMPLETE)
  {
    fprintf(stderr, "glCheckFramebufferStatus: error %p", status);
    return;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // Register for Resize event
  mGraphicsModule->RegisterForResize(GlobalKey(), [this](const ResizeEvent& event) {this->OnResize(event);});
}

void OpenGLPostProcessBuffer::InitializeQuad()
{
  GLfloat verts[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f
  };

  glGenBuffers(1, &mFboVertices);
  glBindBuffer(GL_ARRAY_BUFFER, mFboVertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLPostProcessBuffer::InitializeProgram()
{
  mProgram = glCreateProgram();
  LoadShader("postprocess");
  glAttachShader(mProgram, mShader->GetVertShader());
  glAttachShader(mProgram, mShader->GetFragShader());
  glLinkProgram(mProgram);

  GLint linkOk;
  glGetProgramiv(mProgram, GL_LINK_STATUS, &linkOk);

  if (!linkOk)
  {
    fprintf(stderr, "glLinkProgram: error");
    return;
  }

  glValidateProgram(mProgram);
  GLint validateOk;
  glGetProgramiv(mProgram, GL_VALIDATE_STATUS, &validateOk);

  if (!validateOk)
  {
    fprintf(stderr, "glValidate: error");
    return;
  }

  const char* attributeName = "v_coord";
  mAttributeVcoord = glGetAttribLocation(mProgram, attributeName);

  if (mAttributeVcoord == -1)
  {
    fprintf(stderr, "Could not bind attribute %s\n", attributeName);
    return;
  }

  const char* uniformName = "fbo_texture";
  mUniformFboTexture = glGetUniformLocation(mProgram, uniformName);

  if (mUniformFboTexture == -1)
  {
    fprintf(stderr, "Could not bind uniform %s\n", uniformName);
    return;
  }
}

void OpenGLPostProcessBuffer::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
}

void OpenGLPostProcessBuffer::Unbind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLPostProcessBuffer::Draw()
{
  glUseProgram(mProgram);

  GLenum error = glGetError();
  auto errStr = glewGetErrorString(error);

  GLuint texLoc = glGetUniformLocation(mProgram, "fbo_texture");
  glUniform1i(texLoc, GL_TEXTURE0 + mFboTextureSlot);

  error = glGetError();
  errStr = glewGetErrorString(error);

  glActiveTexture(GL_TEXTURE0 + mFboTextureSlot);
  glBindTexture(GL_TEXTURE_2D, 0);

  error = glGetError();
  errStr = glewGetErrorString(error);

  // bind dt for temp shader
  Engine* engine = mGraphicsModule->GetEngine();
  double dt = engine->GetDt();
  GLint loc = glGetUniformLocation(mProgram, "offset");

  error = glGetError();
  errStr = glewGetErrorString(error);

  glUniform1f(loc, static_cast<float>(dt));

  error = glGetError();
  errStr = glewGetErrorString(error);

  //GLfloat verts[] = {
  //  -1.0f, -1.0f,
  //  1.0f, -1.0f,
  //  -1.0f,  1.0f,
  //  1.0f,  1.0f
  //};

  glEnableVertexAttribArray(mAttributeVcoord);

  error = glGetError();
  errStr = glewGetErrorString(error);

  glBindBuffer(GL_ARRAY_BUFFER, mFboVertices);

  error = glGetError();
  errStr = glewGetErrorString(error);

  glVertexAttribPointer(mAttributeVcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

  error = glGetError();
  errStr = glewGetErrorString(error);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  error = glGetError();
  errStr = glewGetErrorString(error);

  glDisableVertexAttribArray(mAttributeVcoord);

  error = glGetError();
  errStr = glewGetErrorString(error);
}

void OpenGLPostProcessBuffer::LoadShader(std::string shaderName)
{
  if (mShader)
  {
    delete mShader;
  }

  std::string assetsDir = Utils::GetAssetsDirectory();
  std::string vertPath = assetsDir + "Shaders/" + shaderName + ".vert";
  std::string fragPath = assetsDir + "Shaders/" + shaderName + ".frag";
  mShader = new OpenGLShader(shaderName.c_str(), vertPath.c_str(), fragPath.c_str());
}

void OpenGLPostProcessBuffer::OnResize(const ResizeEvent& event)
{
  int width = static_cast<int>(event.newSize[0]);
  int height = static_cast<int>(event.newSize[1]);

  glBindTexture(GL_TEXTURE_2D, mFboTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
               0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);

  glBindRenderbuffer(GL_RENDERBUFFER, mRboDepth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

} // End of Elba namespace
