#pragma once

#include <glm/vec3.hpp>

#include "Elba/Core/Component.hpp"

#include "Elba/Graphics/OpenGL/Submesh.hpp"
#include "Elba/Graphics/OpenGL/Texture.hpp"

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

  std::vector<OpenGL::Pixel> mMasterImage;
  int mMasterWidth;
  int mMasterHeight;

  void OnTextureChange(const OpenGL::TextureChangeEvent& event);
  
  void Interpolate(int screenWidth, int screenHeight);
  void NearestNeighborInterpolation(OpenGL::Texture* texture, int screenWidth, int screenHeight, std::vector<OpenGL::Pixel>& result);
  OpenGL::Pixel NearestNeighborValue(int x, int y, float widthRatio, float heightRatio);

  void BilinearInterpolation(OpenGL::Texture* texture, int screenWidth, int screenHeight, std::vector<OpenGL::Pixel>& result);
  OpenGL::Pixel BilinearValue(int x, int y, float widthRatio, float heightRatio);

  int mScreenWidth;
  int mScreenHeight;
};

} // End of Elba namespace
