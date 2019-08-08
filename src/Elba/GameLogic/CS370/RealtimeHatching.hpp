#pragma once

#include <vector>

#include "Elba/Core/Component.hpp"

#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"


namespace Elba
{
class RealtimeHatching : public Component
{
public:
  RealtimeHatching(Object* parent);

  void Initialize() final;

private:
  void LoadHatchingTextures();

  // Texture for tones 1,2,3, in channels R,G,B, respectively
  std::vector<Pixel> mToneTexturesLight;

  // Texture for tones 4,5,6, in channels R,G,B, respectively
  std::vector<Pixel> mToneTexturesDark;

  OpenGLTexture* mLightTextures;
  OpenGLTexture* mDarkTextures;
};
} // End of Elba namespace
