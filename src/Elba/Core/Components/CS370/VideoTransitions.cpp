#include "Elba/Engine.hpp"
#include "Elba/Core/Object.hpp"
#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Components/CS370/VideoTransitions.hpp"

#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLPostProcess.hpp"

#include "Elba/Utilities/Utils.hpp"

namespace Elba
{
VideoTransitions::VideoTransitions(Object* parent)
  : Component(parent)
  , mProgram(nullptr)
  , mTransitionAmount(0.0f)
  , mTargetTransitionAmount(0.0f)
  , mTransitionMode(0)
  , mStaticImage(nullptr)
{
}

void VideoTransitions::Initialize()
{
  // load the static image
  std::string assetDir = Utils::GetAssetsDirectory();
  std::string texPath = assetDir + "Textures/SunriseOverEasternSea.png";
  mStaticImage = new OpenGLTexture(texPath);
  auto& image = mStaticImage->GetImage();
  
  Engine* engine = GetParent()->GetCoreModule()->GetEngine();
  OpenGLModule* glModule = static_cast<OpenGLModule*>(engine->GetGraphicsModule());
  OpenGLPostProcess* postProcess = glModule->GetPostProcess();
  postProcess->SetTransitionTexture(image, mStaticImage->GetWidth(), mStaticImage->GetHeight());
}

void VideoTransitions::Update(double dt)
{
  // update transition amount
  if (mTransitionAmount < mTargetTransitionAmount)
  {
    mTransitionAmount += dt;
  }
  else if (mTransitionAmount > mTargetTransitionAmount)
  {
    mTransitionAmount -= dt;
  }

  if (mTransitionAmount < 0.0f)
  {
    mTransitionAmount = 0.0f;
  }
  else if (mTransitionAmount > 1.0f)
  {
    mTransitionAmount = 1.0f;
  }

  if (mProgram)
  {
    Elba::OpenGLUniformFloat amountUniform("transitionAmount", mTransitionAmount);
    mProgram->SetUniform(amountUniform);

    Elba::OpenGLUniformInt modeUniform("transitionMode", mTransitionMode);
    mProgram->SetUniform(modeUniform);
  }
}

void VideoTransitions::SetProgram(OpenGLProgram* program)
{
  mProgram = program;
}

void VideoTransitions::TriggerTransitionToRealTime()
{
  mTargetTransitionAmount = 0.0f;
}

void VideoTransitions::TriggerTransitionToStaticImage()
{
  mTargetTransitionAmount = 1.0f;
}

void VideoTransitions::SetMode(int mode)
{
}
} // End of Elba namespace
