#include <iostream>

#include "Elba/Engine.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLFramebuffer.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLProgram.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLVertexShader.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLFragmentShader.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"
#include "Elba/Utilities/Utils.hpp"

namespace Elba
{
OpenGLFramebuffer::OpenGLFramebuffer(OpenGLModule* graphicsModule)
  : mGraphicsModule(graphicsModule)
  , mProgram(nullptr)
  , mDoImageNegative(0)
  , mDoLogTransform(0)
  , mDoGammaTransform(0)
  , mValueC(1.0f)
  , mValueGamma(0.5f)
  , mDoEdgeDetection(0)
{
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
  delete mProgram;
}

void OpenGLFramebuffer::InitializeBuffers(int textureSlot)
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
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, mWidth, mHeight, 0, GL_RGBA, GL_FLOAT, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
  mGraphicsModule->RegisterForResize(GlobalKey(), [this](const ResizeEvent& event)
  {
    this->OnResize(event);
  });
}

void OpenGLFramebuffer::InitializeQuad()
{
  float quadVertices[] = {
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f, // top left
    -1.0f, -1.0f,  0.0f, 0.0f, // bottom left
     1.0f, -1.0f,  1.0f, 0.0f, // bottom right

    -1.0f,  1.0f,  0.0f, 1.0f, // top left
     1.0f, -1.0f,  1.0f, 0.0f, // bottom right
     1.0f,  1.0f,  1.0f, 1.0f  // top right
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

void OpenGLFramebuffer::InitializeProgram()
{
  LoadShaders("postprocess");
}

void OpenGLFramebuffer::PreRender()
{
  glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
}

void OpenGLFramebuffer::PostRender()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_DEPTH_TEST);
}

void OpenGLFramebuffer::Draw()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  mProgram->Use();

  glActiveTexture(GL_TEXTURE0);
  mProgram->SetUniform("screenTexture", 0);
  mProgram->SetUniform("doNegative", mDoImageNegative);
  mProgram->SetUniform("doLog", mDoLogTransform);
  mProgram->SetUniform("doGamma", mDoGammaTransform);
  mProgram->SetUniform("c", mValueC);
  mProgram->SetUniform("gamma", mValueGamma);
  mProgram->SetUniform("doSobel", mDoEdgeDetection);

  glBindVertexArray(mVAO);
  glBindTexture(GL_TEXTURE_2D, mTextureColorBuffer);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
}

void OpenGLFramebuffer::LoadShaders(std::string shaderName)
{
  if (mProgram)
  {
    delete mProgram;
  }

  std::string assetsDir = Utils::GetAssetsDirectory();

  std::string vertPath = assetsDir + "Shaders/" + shaderName + ".vert";
  UniquePtr<OpenGLVertexShader> vertShader = NewUnique<OpenGLVertexShader>(vertPath);
  
  std::string fragPath = assetsDir + "Shaders/" + shaderName + ".frag";
  UniquePtr<OpenGLFragmentShader> fragShader = NewUnique<OpenGLFragmentShader>(fragPath);

  mProgram = new OpenGLProgram(shaderName.c_str());
  mProgram->AttachShader(std::move(vertShader));
  mProgram->AttachShader(std::move(fragShader));
  mProgram->Link();
}

GLuint OpenGLFramebuffer::GetTexture() const
{
  return mTextureColorBuffer;
}

void OpenGLFramebuffer::SetTexture(GLuint texId)
{
  mTextureColorBuffer = texId;
}

void OpenGLFramebuffer::SetDoImageNegative(int value)
{
  mDoImageNegative = value;
}

void OpenGLFramebuffer::SetDoLogTransform(int value)
{
  mDoLogTransform = value;
}

void OpenGLFramebuffer::SetDoGammaTransform(int value)
{
  mDoGammaTransform = value;
}

void OpenGLFramebuffer::SetDoEdgeDetection(int value)
{
  mDoEdgeDetection = value;
}

void OpenGLFramebuffer::SetValueC(float value)
{
  mValueC = value;
}

void OpenGLFramebuffer::SetValueGamma(float value)
{
  mValueGamma = value;
}

void OpenGLFramebuffer::ResizeWithCurrentDimensions()
{
  ResizeEvent event;
  event.newSize.x = static_cast<float>(mWidth);
  event.newSize.y = static_cast<float>(mHeight);
  event.oldSize.x = static_cast<float>(mWidth);
  event.oldSize.y = static_cast<float>(mHeight);

  OnResize(event);
}

void OpenGLFramebuffer::OnResize(const ResizeEvent& event)
{
  mWidth = static_cast<int>(event.newSize[0]);
  mHeight = static_cast<int>(event.newSize[1]);

  glBindFramebuffer(GL_FRAMEBUFFER, mFbo);

  // create color attachment texture
  glBindTexture(GL_TEXTURE_2D, mTextureColorBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, mWidth, mHeight, 0, GL_RGBA, GL_FLOAT, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureColorBuffer, 0);

  // create renderbuffer for depth and stencil attachment
  glBindRenderbuffer(GL_RENDERBUFFER, mRbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRbo);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    throw std::exception("Framebuffer is garbage");
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // End of Elba namespace
