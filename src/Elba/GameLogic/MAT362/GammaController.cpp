#include "Elba/Core/Object.hpp"
#include "Elba/GameLogic/MAT362/GammaController.hpp"

#include "Elba/Core/CoreModule.hpp"
#include "Elba/Engine.hpp"

#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"

namespace Elba
{
GammaController::GammaController(Object* parent) 
  : Component(parent)
{
  mModel = parent->GetComponent<Model>();
  mGraphics = static_cast<OpenGLModule*>(GetParent()->GetCoreModule()->GetEngine()->GetGraphicsModule());
}

void GammaController::Initialize()
{
  // set up Takagi Sugeno system for gamma control

  // if average intensity is [0, 110], gamma should be high (g > 1). --->  if x is [0, 110] then g = 1.0f + log2(3.0f * 1 - x)
  PiecewiseLinear piecewise;
  piecewise.AddPoint(0.0f, 1.0f);
  piecewise.AddPoint(55.0f, 1.0f);
  piecewise.AddPoint(110.0f, 0.0f);
  mFuzzySystem.AddRule(piecewise, [](float x) { return 1.0f + log2(3.0f * (1.0001f - x));});

  // if average intensity is [90, 170], gamma should be one (g = 1). --->  if x is[90, 170] then g = 1
  piecewise.ClearPoints();
  piecewise.AddPoint(90.0f, 0.0f);
  piecewise.AddPoint(130.0f, 1.0f);
  piecewise.AddPoint(170.0f, 0.0f);
  mFuzzySystem.AddRule(piecewise, [](float x) { return 1.0f; });

  // if average intensity is [140, 255], gamma should be low (g < 1). --->  if x is[140, 255] then g = x + 0.01f
  piecewise.ClearPoints();
  piecewise.AddPoint(150.0f, 0.0f);
  piecewise.AddPoint(200.0f, 1.0f);
  piecewise.AddPoint(255.0f, 1.0f);
  mFuzzySystem.AddRule(piecewise, [](float x) { return  1.00001f - (0.65f * x); });
}

void GammaController::Update(double dt)
{
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());
  auto& submeshes = mesh->GetSubmeshes();
  OpenGLTexture* texture = submeshes.begin()->GetTexture(TextureType::Diffuse);
  auto& image = texture->GetImage();

  unsigned char average = CalculateAverageIntensity(image);

  float gammaValue = mFuzzySystem.CalculateSystemOutput(static_cast<float>(average));
  mGraphics->GetFramebuffer()->SetValueGamma(gammaValue);
}

unsigned char GammaController::CalculateAverageIntensity(std::vector<Pixel>& image)
{
  unsigned int sum = 0;

  for (Pixel& pixel : image)
  {
    unsigned char intensity = static_cast<unsigned char>(0.3f * static_cast<float>(pixel.r) + 0.59f * static_cast<float>(pixel.g) + 0.11f * static_cast<float>(pixel.b));
    sum += intensity;
  }

  return static_cast<unsigned char>(sum / image.size());
}
} // End of Elba namespace
