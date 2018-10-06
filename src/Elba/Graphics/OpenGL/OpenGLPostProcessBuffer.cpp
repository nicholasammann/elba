#include <iostream>

#include "Elba/Engine.hpp"
#include "Elba/Graphics/OpenGL/OpenGLPostProcessBuffer.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLShader.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"
#include "Elba/Utilities/Utils.hpp"

namespace Elba
{
OpenGLPostProcessBuffer::OpenGLPostProcessBuffer(OpenGLModule* graphicsModule)
  : mGraphicsModule(graphicsModule)
  , mShader(nullptr)
  , mTexture(new OpenGLTexture())
{
}

OpenGLPostProcessBuffer::~OpenGLPostProcessBuffer()
{
  glDeleteRenderbuffers(1, &mRbo);
  glDeleteTextures(1, &mFboTexture);
  glDeleteFramebuffers(1, &mFbo);
  glDeleteBuffers(1, &mFboVertices);
  //glDeleteProgram(mProgram);
}

void OpenGLPostProcessBuffer::InitializeBuffers(int textureSlot)
{
  // store texture slot
  mFboTextureSlot = textureSlot;

  // width, height
  std::pair<int, int> screenSize = mGraphicsModule->GetScreenDimensions();
  mWidth = screenSize.first;
  mHeight = screenSize.second;

  // generate buffers
  glGenFramebuffers(1, &mMSFbo);
  glGenFramebuffers(1, &mFbo);
  glGenRenderbuffers(1, &mRbo);

  // initialize render buffer storage with multisampled color buffer
  glBindFramebuffer(GL_FRAMEBUFFER, mMSFbo);
  glBindRenderbuffer(GL_RENDERBUFFER, mRbo);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_RGB, mWidth, mHeight);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mRbo);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    fprintf(stderr, "glCheckFramebufferStatus: error");
    return;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, mFbo);

  mTexture->SetWidth(mWidth);
  mTexture->SetHeight(mHeight);
  mTexture->GenerateFramebufferTexture();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // Register for Resize event
  mGraphicsModule->RegisterForResize(GlobalKey(), [this](const ResizeEvent& event) {this->OnResize(event);});
}

void OpenGLPostProcessBuffer::InitializeQuad()
{
  GLuint VBO;
  GLfloat verts[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f
  };

  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

  glBindVertexArray(mVAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLPostProcessBuffer::InitializeProgram()
{
  LoadShader("postprocess");

  mShader->UseShaderProgram();
  GLuint prg = mShader->GetShaderProgram();

  //glAttachShader(mProgram, mShader->GetVertShader());
  //glAttachShader(mProgram, mShader->GetFragShader());
  //glLinkProgram(mProgram);
  //
  //GLint linkOk;
  //glGetProgramiv(mProgram, GL_LINK_STATUS, &linkOk);
  //
  //if (!linkOk)
  //{
  //  fprintf(stderr, "glLinkProgram: error");
  //  return;
  //}
  //
  //glValidateProgram(mProgram);
  //GLint validateOk;
  //glGetProgramiv(mProgram, GL_VALIDATE_STATUS, &validateOk);
  //
  //if (!validateOk)
  //{
  //  fprintf(stderr, "glValidate: error");
  //  return;
  //}

  //const char* attributeName = "v_coord";
  //mAttributeVcoord = glGetAttribLocation(prg, attributeName);
  //
  //if (mAttributeVcoord == -1)
  //{
  //  fprintf(stderr, "Could not bind attribute %s\n", attributeName);
  //  return;
  //}

  //const char* uniformName = "fbo_texture";
  //mUniformFboTexture = glGetUniformLocation(prg, uniformName);
  //
  //if (mUniformFboTexture == -1)
  //{
  //  fprintf(stderr, "Could not bind uniform %s\n", uniformName);
  //  return;
  //}
}

void OpenGLPostProcessBuffer::Bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, mMSFbo);
}

void OpenGLPostProcessBuffer::Unbind()
{
  glBindFramebuffer(GL_READ_FRAMEBUFFER, mMSFbo);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFbo);
  glBlitFramebuffer(0, 0, mWidth, mHeight, 0, 0, mWidth, mHeight,
                    GL_COLOR_BUFFER_BIT, GL_NEAREST);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLPostProcessBuffer::Draw()
{
  GLenum error = glGetError();

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  mShader->UseShaderProgram();
  GLuint prg = mShader->GetShaderProgram();

  mTexture->SetUniform(prg, "fbo_texture", 0);
  mTexture->Bind(0);

  // bind dt for temp shader
  Engine* engine = mGraphicsModule->GetEngine();
  double dt = engine->GetDt();
  mShader->SetFloat("offset", dt);

  glEnableVertexAttribArray(mAttributeVcoord);
  glBindBuffer(GL_ARRAY_BUFFER, mFboVertices);
  glVertexAttribPointer(mAttributeVcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableVertexAttribArray(mAttributeVcoord);

  mTexture->Unbind();
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
  mWidth = static_cast<int>(event.newSize[0]);
  mHeight = static_cast<int>(event.newSize[1]);

  glBindTexture(GL_TEXTURE_2D, mFboTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, 
               GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);

  glBindRenderbuffer(GL_RENDERBUFFER, mRbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 
                        mWidth, mHeight);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

} // End of Elba namespace
