#pragma once

#include <glm/vec3.hpp>

#include "Elba/Core/Component.hpp"

#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"

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

  enum InterpolationMode
  {
    None,
    NearestNeighbor,
    Bilinear
  };

  void SetInterpolationMode(InterpolationMode mode);

private:
  Transform* mTransform;
  Model* mModel;

  InterpolationMode mInterpolationMode;

  unsigned char* mMasterImage;
  int mMasterWidth;
  int mMasterHeight;

  void OnTextureChange(const TextureChangeEvent& event);
  
  void Interpolate(int screenWidth, int screenHeight);
  void NearestNeighborInterpolation(OpenGLTexture* texture);
  void BilinearInterpolation(OpenGLTexture* texture);

  int mScreenWidth;
  int mScreenHeight;
};

} // End of Elba namespace
