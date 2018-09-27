
#include "Elba/Core/Object.hpp"
#include "Elba/Core/Components/CS370/ResizeHandler.hpp"

#include "Elba/Core/Components/Model.hpp"
#include "Elba/Core/Components/Transform.hpp"

#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

namespace Elba
{

ResizeHandler::ResizeHandler(Object* parent)
  : Component(parent)
  , mTransform(nullptr)
  , mModel(nullptr)
  , mInterpolationMode(InterpolationMode::None)
{
}

void ResizeHandler::Initialize()
{
  mTransform = GetParent()->GetComponent<Elba::Transform>();
  mModel = GetParent()->GetComponent<Elba::Model>();
}

void ResizeHandler::Resize(int screenWidth, int screenHeight)
{
  mTransform->SetWorldScale(glm::vec3(static_cast<float>(screenWidth), 1.0f, static_cast<float>(screenHeight)));
  Interpolate(screenWidth, screenHeight);
}

void ResizeHandler::SetInterpolationMode(InterpolationMode mode)
{
  mInterpolationMode = mode;
}

void ResizeHandler::OnTextureChange(const TextureChangeEvent& event)
{
  mMasterImage = event.newTexture->GetImage();
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
        break;
      }
    }
  }
}

void ResizeHandler::NearestNeighborInterpolation(OpenGLTexture* texture)
{
}

void ResizeHandler::BilinearInterpolation(OpenGLTexture* texture)
{
}

} // End of Elba namespace

