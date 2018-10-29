#pragma once

#include "Elba/Core/Component.hpp"
#include "Elba/Core/Components/Model.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"
#include "Elba/Utilities/Math/Fuzzy/TakagiSugenoSystem.hpp"

namespace Elba
{
class GammaController : public Component
{
public:
  GammaController(Object* parent);
  void Initialize() override;
  void Update(double dt) override;

private:
  Model* mModel;
  TakagiSugenoSystem mFuzzySystem;

  OpenGLModule* mGraphics;

  unsigned char CalculateAverageIntensity(std::vector<Pixel>& image);
};
} // End of Elba namespace

/*
// For gamma correction

if image is dark, gamma should be low (g <= 1)

if image is fine, gamma should be middle (g = 1)

if image is light, gamma should be high (g >= 1)

          CAN BE IMPLEMENTED AS

if average intensity is [0, 110], gamma should be low (g < 1). --->  if x is [0, 110] then g = x / 110 + 0.01

if average intensity is [90, 170], gamma should be low (g < 1). --->  if x is [0, 110] then g = 1

if average intensity is [140, 255], gamma should be low (g < 1). --->  if x is [0, 110] then g = 1 + log base 2(x / 25)
*/




