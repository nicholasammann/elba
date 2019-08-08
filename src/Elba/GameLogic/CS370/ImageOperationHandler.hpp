#pragma once

#include <vector>

#include "Elba/Core/Component.hpp"
#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

namespace Elba
{

struct BigPixel
{
  int r, g, b, a;
};

class ImageOperationHandler : public Component
{
public:
  ImageOperationHandler(Object* parent);

  void Initialize() final;

  void Resize(const ResizeEvent& event);

  void SetImageA(OpenGLTexture* image);
  void SetImageB(OpenGLTexture* image);

  void DoNone();
  void DoAddition();
  void DoSubtraction();
  void DoProduct();

  void SetImageNegative(int value);
  void SetLogTransform(int value);
  void SetGammaTransform(int value);

  void SetCValue(float value);
  void SetGammaValue(float value);

private:
  OpenGLTexture* mImageA;
  OpenGLTexture* mImageB;

  int mScreenWidth;
  int mScreenHeight;

  std::vector<Pixel> GetAddition();
  std::vector<Pixel> GetSubtraction();
  std::vector<Pixel> GetProduct();

  void GetResizedImages(std::vector<Pixel>& resizedA, 
                        std::vector<Pixel>& resizedB);

  void NormalizeImage(std::vector<BigPixel>& image, float ratio, std::vector<Pixel>& result);

  OpenGLTexture* GetObjectTexture();

  OpenGLFramebuffer* GetFramebuffer();
  OpenGLFramebuffer* mFramebuffer;
};

} // End of Elba namespace
