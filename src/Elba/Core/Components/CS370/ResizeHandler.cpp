
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
  mMasterImage = event.newTexture->GetImage();
  mMasterWidth = event.newTexture->GetWidth();
  mMasterHeight = event.newTexture->GetHeight();
}

void ResizeHandler::Interpolate(int screenWidth, int screenHeight)
{
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());

  auto it = mesh->GetSubmeshes().begin();

  if (it != mesh->GetSubmeshes().end())
  {
    OpenGLTexture* texture = it->GetDiffuseTexture();

    // do some form of interpolation
    switch (mInterpolationMode)
    {
      case InterpolationMode::NearestNeighbor:
      {
        NearestNeighborInterpolation(texture);
        break;
      }

      case InterpolationMode::Bilinear:
      {
        BilinearInterpolation(texture);
        break;
      }

      case InterpolationMode::None:
      {
        // EVERYTHING IS AWFUL NO INTERPOLATION OH MY GOD
        break;
      }
    }
  }
}

void ResizeHandler::NearestNeighborInterpolation(OpenGLTexture* texture)
{
  int newWidth = texture->GetWidth();
  int newHeight = texture->GetHeight();
  int stride = newWidth * 3;

  unsigned char* newImage = new unsigned char[stride * newHeight];

  for (int y = 0; y < newHeight; ++y)
  {
    for (int x = 0; x < stride; ++x)
    {
      // nearest neighbor interpolation
    }
  }
}

void ResizeHandler::BilinearInterpolation(OpenGLTexture* texture)
{
  int newWidth = texture->GetWidth();
  int newHeight = texture->GetHeight();
  int stride = newWidth * 3;

  unsigned char* newImage = new unsigned char[stride * newHeight];

  for (int y = 0; y < newHeight; ++y)
  {
    for (int x = 0; x < stride; x += 3)
    {
      // bilinear interpolation
      
      // alpha = (x - x1) / (x2 - x1)
      float alpha = ()

      // beta = (y - y1) / (y2 - y1)

      // f(x, y1) = (1 - alpha) * f(x1, y1) + alpha * f(x2, y1)
      // f(x, y2) = (1 - alpha) * f(x1, y2) + alpha * f(x2, y2)

      // f(x,y) = (1 - beta) * f(x, y1) + beta * f(x, y2)


    }
  }
}

} // End of Elba namespace

