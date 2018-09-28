#include <cmath>

#include "Elba/Core/Object.hpp"
#include "Elba/Core/Components/CS370/ResizeHandler.hpp"

#include "Elba/Core/Components/Model.hpp"
#include "Elba/Core/Components/Transform.hpp"

#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

namespace Elba
{

ResizeHandler::ResizeHandler(Object* parent)
  : Component(parent)
  , mTransform(nullptr)
  , mModel(nullptr)
  , mInterpolationMode(InterpolationMode::None)
  , mMasterImage(nullptr)
  , mMasterWidth(800)
  , mMasterHeight(600)
  , mScreenWidth(800)
  , mScreenHeight(600)
{
}

void ResizeHandler::Initialize()
{
  mTransform = GetParent()->GetComponent<Elba::Transform>();
  mModel = GetParent()->GetComponent<Elba::Model>();

  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());
  auto sbm_it = mesh->GetSubmeshes().begin();

  if (sbm_it != mesh->GetSubmeshes().end())
  {
    // Register to be notified when the texture on the submesh changes
    sbm_it->RegisterForTextureChange(GlobalKey(), [this](const TextureChangeEvent& event)
    {
      this->OnTextureChange(event);
    });
  }
}

void ResizeHandler::Resize(int screenWidth, int screenHeight)
{
  // Store width and height for user changes interpolation
  mScreenWidth = screenWidth;
  mScreenHeight = screenHeight;

  // Resize image to match screen size
  mTransform->SetWorldScale(glm::vec3(static_cast<float>(screenWidth), 1.0f, static_cast<float>(screenHeight)));

  // Perform interpolation
  Interpolate(screenWidth, screenHeight);
}

void ResizeHandler::SetInterpolationMode(InterpolationMode mode)
{
  mInterpolationMode = mode;

  // Perform interpolation again with different mode
  Interpolate(mScreenWidth, mScreenHeight);
}

void ResizeHandler::OnTextureChange(const TextureChangeEvent& event)
{
  mMasterWidth = event.newTexture->GetWidth();
  mMasterHeight = event.newTexture->GetHeight();

  // delete old master image
  if (mMasterImage)
  {
    delete [] mMasterImage;
  }

  // allocate new master image
  mMasterImage = new unsigned char[mMasterHeight * mMasterWidth * 3];

  for (int y = 0; y < mMasterHeight; ++y)
  {
    for (int x = 0; x < mMasterWidth * 3; ++x)
    {
      int ind = y * mMasterWidth + x;
      mMasterImage[ind] = event.newTexture->GetImage()[ind];
    }
  }
}

void ResizeHandler::Interpolate(int screenWidth, int screenHeight)
{
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());

  auto it = mesh->GetSubmeshes().begin();

  if (it != mesh->GetSubmeshes().end())
  {
    OpenGLTexture* texture = it->GetDiffuseTexture();
    unsigned char* image = nullptr;

    // do some form of interpolation
    switch (mInterpolationMode)
    {
      case InterpolationMode::NearestNeighbor:
      {
        image = NearestNeighborInterpolation(texture, screenWidth, screenHeight);
        break;
      }

      case InterpolationMode::Bilinear:
      {
        image = BilinearInterpolation(texture, screenWidth, screenHeight);
        break;
      }

      case InterpolationMode::None:
      {
        // EVERYTHING IS AWFUL NO INTERPOLATION OH MY GOD
        return;
      }
    }

    // recreate the opengl texture
    texture->SetImage(image, screenWidth, screenHeight);
    texture->RebindTexture();
  }
}

unsigned char* ResizeHandler::NearestNeighborInterpolation(OpenGLTexture* texture, int screenWidth, int screenHeight)
{
  int stride = screenWidth * 3;

  unsigned char* newImage = new unsigned char[stride * screenHeight];

  

  for (int y = 0; y < screenHeight; ++y)
  {
    for (int x = 0; x < stride; ++x)
    {
      // nearest neighbor interpolation
      
      // find the nearest point and make it that color
      
    }
  }

  return newImage;
}

unsigned char* ResizeHandler::BilinearInterpolation(OpenGLTexture* texture, int screenWidth, int screenHeight)
{
  int stride = screenWidth * 3;

  float widthRatio = static_cast<float>(mMasterWidth) / static_cast<float>(screenWidth);
  float heightRatio = static_cast<float>(mMasterHeight) / static_cast<float>(screenHeight);

  unsigned char* newImage = new (std::nothrow) unsigned char[stride * screenHeight];

  if (newImage == nullptr)
  {
    throw std::exception("WHAT THE FUCK");
  }

  for (int y = 0; y < screenHeight; ++y)
  {
    for (int x = 0; x < stride; ++x)
    {
      // bilinear interpolation
      int value = BilinearValue(x, y, widthRatio, heightRatio);

      unsigned int index = y * stride + x;

      if (value < 1)
      {
        value = 1;
      }

      newImage[index] = value;
    }
  }

  return newImage;
  texture->SetImage(newImage, screenWidth, screenHeight);
}

int ResizeHandler::BilinearValue(int x, int y, float widthRatio, float heightRatio)
{
  float tX = x * widthRatio;
  float tY = y * heightRatio;

  int x1 = floor(tX);
  int x2 = floor(tX + 1);

  int y1 = floor(tY);
  int y2 = floor(tY + 1);

  // alpha = (x - x1) / (x2 - x1)
  float alpha = (tX - x1) / (x2 - x1);

  // beta = (y - y1) / (y2 - y1)
  float beta = (tY - y1) / (y2 - y1);

  // f(x, y1) = (1 - alpha) * f(x1, y1) + alpha * f(x2, y1)
  float fxy1 = (1.0f - alpha) * mMasterImage[y1 * mMasterWidth * 3 + x1] + alpha * mMasterImage[y1 * mMasterWidth * 3 + x2];

  // f(x, y2) = (1 - alpha) * f(x1, y2) + alpha * f(x2, y2)
  float fxy2 = (1.0f - alpha) * mMasterImage[y2 * mMasterWidth * 3 + x1] + alpha * mMasterImage[y2 * mMasterWidth * 3 + x2];

  // f(x,y) = (1 - beta) * f(x, y1) + beta * f(x, y2)
  float fxy = (1.0f - beta) * fxy1 + beta * fxy2;

  return static_cast<int>(fxy);
}

} // End of Elba namespace

