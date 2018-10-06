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
  , mElapsedTime(0.0f)
{
}

OpenGLPostProcessBuffer::~OpenGLPostProcessBuffer()
{
}

void OpenGLPostProcessBuffer::InitializeBuffers(int textureSlot)
{
  // width, height
  std::pair<int, int> screenSize = mGraphicsModule->GetScreenDimensions();
  mWidth = screenSize.first;
  mHeight = screenSize.second;

  // generate framebuffer
  glGenFramebuffers(1, &mFbo);
  glBindFramebuffer(GL_FRAMEBUFFER, mFbo);

  // create color attachment texture
  glGenTextures(1, &mTextureColorBuffer);
  glBindTexture(GL_TEXTURE_2D, mTextureColorBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureColorBuffer, 0);

  // create renderbuffer for depth and stencil attachment
  glGenRenderbuffers(1, &mRbo);
  glBindRenderbuffer(GL_RENDERBUFFER, mRbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRbo);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    throw std::exception("Framebuffer is garbage");
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // Register for Resize event
  mGraphicsModule->RegisterForResize(GlobalKey(), [this](const ResizeEvent& event) {this->OnResize(event);});
}

void OpenGLPostProcessBuffer::InitializeQuad()
{
  float quadVertices[] = {
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
  };

  GLuint VBO;
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)(2 * sizeof(float)));
}

void OpenGLPostProcessBuffer::InitializeProgram()
{
  LoadShader("postprocess");
}

void OpenGLPostProcessBuffer::PreRender()
{
  glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
  glEnable(GL_DEPTH_TEST);
}

void OpenGLPostProcessBuffer::PostRender()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_DEPTH_TEST);
}

void OpenGLPostProcessBuffer::Draw()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  mShader->UseShaderProgram();
  glActiveTexture(GL_TEXTURE0);
  mShader->SetInt("screenTexture", 0);

  Engine* engine = mGraphicsModule->GetEngine();
  float dt = static_cast<float>(engine->GetDt());
  mElapsedTime += dt;
  mShader->SetFloat("offset", mElapsedTime);

  glBindVertexArray(mVAO);
  glBindTexture(GL_TEXTURE_2D, mTextureColorBuffer);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
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

  //glBindTexture(GL_TEXTURE_2D, mFboTexture);
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, 
  //             GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  //glBindTexture(GL_TEXTURE_2D, 0);
  //
  //glBindRenderbuffer(GL_RENDERBUFFER, mRbo);
  //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 
  //                      mWidth, mHeight);
  //glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

} // End of Elba namespace
