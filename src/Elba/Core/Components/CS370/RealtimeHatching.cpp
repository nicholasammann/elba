#include <stbi/stb_image.h>

#include "Elba/Core/Object.hpp"
#include "Elba/Core/Components/CS370/RealtimeHatching.hpp"

#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"

#include "Elba/Utilities/Utils.hpp"

namespace Elba
{
RealtimeHatching::RealtimeHatching(Object* parent)
  : Component(parent)
{
}

void RealtimeHatching::Initialize()
{
  LoadHatchingTextures();
}

GLuint RealtimeHatching::GetLightTextures() const
{
  return mLightTexturesId;
}

GLuint RealtimeHatching::GetDarkTextures() const
{
  return mDarkTexturesId;
}

void RealtimeHatching::LoadHatchingTextures()
{
  std::string assetDir = Utils::GetAssetsDirectory();
  std::string hatchDir = assetDir + "Textures/Hatching/";

  int width, height, channels;

  std::string tone1Dir = hatchDir + "default03.bmp";
  unsigned char* tone1 = stbi_load(tone1Dir.c_str(), &width, &height, &channels, 3);

  std::string tone2Dir = hatchDir + "default13.bmp";
  unsigned char* tone2 = stbi_load(tone2Dir.c_str(), &width, &height, &channels, 3);

  std::string tone3Dir = hatchDir + "default23.bmp";
  unsigned char* tone3 = stbi_load(tone3Dir.c_str(), &width, &height, &channels, 3);

  std::string tone4Dir = hatchDir + "default33.bmp";
  unsigned char* tone4 = stbi_load(tone4Dir.c_str(), &width, &height, &channels, 3);

  std::string tone5Dir = hatchDir + "default43.bmp";
  unsigned char* tone5 = stbi_load(tone5Dir.c_str(), &width, &height, &channels, 3);

  std::string tone6Dir = hatchDir + "default53.bmp";
  unsigned char* tone6 = stbi_load(tone6Dir.c_str(), &width, &height, &channels, 3);

  mToneTexturesLight.resize(height * width);
  mToneTexturesDark.resize(height * width);

  // Load the tone textures (grayscale) into two texture buffers
  for (int i = 0; i < height * width * channels; i += channels)
  {
    int index = i / 3;

    mToneTexturesLight[index].r = tone1[i];
    mToneTexturesLight[index].g = tone2[i + 1];
    mToneTexturesLight[index].b = tone3[i + 2];

    mToneTexturesDark[index].r = tone4[i];
    mToneTexturesDark[index].g = tone5[i + 1];
    mToneTexturesDark[index].b = tone6[i + 2];
  }

  mLightTextures = new OpenGLTexture();
  mLightTextures->SetUniformName("lightToneTextures");
  mLightTextures->SetImage(mToneTexturesLight, width, height);
  mLightTextures->GenerateTexture();

  mDarkTextures = new OpenGLTexture();
  mLightTextures->SetUniformName("darkToneTextures");
  mDarkTextures->SetImage(mToneTexturesDark, width, height);
  mDarkTextures->GenerateTexture();

  // add textures to submesh
  Model* model = GetParent()->GetComponent<Model>();
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(model->GetMesh());
  auto& submeshes = mesh->GetSubmeshes();

  for (OpenGLSubmesh& subm : submeshes)
  {
    subm.AddTexture(mLightTextures);
    subm.AddTexture(mDarkTextures);
  }
}
} // End of Elba namespace
