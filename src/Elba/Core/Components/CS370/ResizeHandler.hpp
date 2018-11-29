#pragma once

#include <glm/vec3.hpp>

#include "Elba/Core/Component.hpp"

#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

#include "Elba/Utilities/Math/Fourier/FourierTransform.hpp"

namespace Elba
{

class Transform;
class Model;

class ResizeHandler : public Component
{
public:
  ResizeHandler(Object* parent);

  void Initialize() final;

  void Resize(int screenWidth, int screenHeight);

  enum class InterpolationMode
  {
    None,
    NearestNeighbor,
    Bilinear
  };

  enum class FourierMethod
  {
    None,
    DirectMethod,
    SeparableMethod,
    FastFourier
  };

  enum class CurrentImage
  {
    Original,
    Frequency,
    Transformed
  };

  void SetInterpolationMode(InterpolationMode mode);

  InterpolationMode GetInterpolationMode() const;

  void NearestNeighborInterpolation(std::vector<Pixel>& source, int srcWidth, int srcHeight, 
                                    std::vector<Pixel>& result, int targetWidth, int targetHeight);
  void BilinearInterpolation(std::vector<Pixel>& source, int srcWidth, int srcHeight, 
                             std::vector<Pixel>& result, int targetWidth, int targetHeight);

  void SetImage(const std::vector<Pixel>& image, int width, int height);

  void SetUseHistogramEqualization(bool useHistogram);

  void SetFourierMethod(FourierMethod method);
  void SetCurrentImage(CurrentImage image);


  // Assignment 4
  void ApplyGaussianNoise();
  void ApplySaltPepperNoise();
  void ApplyNoiseReduction();
  void ApplyLocalNoiseReduction();
  void ApplyAdaptiveNoiseReduction();

  void SetGaussianMeanX(float value);
  void SetGaussianMeanY(float value);
  void SetGaussianVarianceX(float value);
  void SetGaussianVarianceY(float value);

  void SetPa(float value);
  void SetPb(float value);

  void SetDeviation(float value);
  void SetSMax(float value);

private:
  Transform* mTransform;
  Model* mModel;

  InterpolationMode mInterpolationMode;

  std::vector<Pixel> mMasterImage;
  int mMasterWidth;
  int mMasterHeight;

  void OnTextureChange(const TextureChangeEvent& event);
  
  void Interpolate(int screenWidth, int screenHeight);
  void NearestNeighborInterpolation(OpenGLTexture* texture, int screenWidth, int screenHeight, std::vector<Pixel>& result);
  Pixel NearestNeighborValue(int x, int y, int width, int height, float widthRatio, float heightRatio, std::vector<Pixel>& src);

  void BilinearInterpolation(OpenGLTexture* texture, int screenWidth, int screenHeight, std::vector<Pixel>& result);
  Pixel BilinearValue(int x, int y, int width, int height, float widthRatio, float heightRatio, std::vector<Pixel>& src);

  int mScreenWidth;
  int mScreenHeight;

  bool mUseHistogramEqualization;
  void HistogramEqualization(std::vector<Pixel>& image);

  FourierMethod mFourierMethod;
  CurrentImage mCurrentImage;
  void DirectFourier(std::vector<Pixel>& image, int w, int h);
  void SeparableFourier(std::vector<Pixel>& image, int w, int h);
  void FastFourier(std::vector<Pixel>& image, int w, int h);

  void CopyToSpatialImage(const std::vector<Pixel>& image, Fourier::SpatialImage& spatial, int w, int h);
  void CopyFromFrequencyImage(const Fourier::FrequencyImage& frequency, std::vector<Pixel>& image, int w, int h);

  std::vector<Pixel> mOriginalImage;
  std::vector<Pixel> mFrequencyImage;
  std::vector<Pixel> mTransformedImage;

  int IndexAt(int x, int y, int w);
  float GaussianNoise(int x, int y);

  // Assignment 4
  float mGaussianMeanX;
  float mGaussianMeanY;
  float mGaussianVarianceX;
  float mGaussianVarianceY;

  float mPa;
  float mPb;

  float mDeviation;

  float mSMax;

};

} // End of Elba namespace
