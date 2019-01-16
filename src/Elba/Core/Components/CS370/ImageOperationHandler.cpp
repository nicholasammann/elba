#include <algorithm>

#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Object.hpp"
#include "Elba/Core/Components/CS370/ResizeHandler.hpp"
#include "Elba/Core/Components/CS370/ImageOperationHandler.hpp"
#include "Elba/Core/Components/Model.hpp"
#include "Elba/Engine.hpp"
#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"

namespace Elba
{
ImageOperationHandler::ImageOperationHandler(Object* parent) 
  : Component(parent)
  , mImageA(nullptr)
  , mImageB(nullptr)
  , mScreenWidth(800)
  , mScreenHeight(600)
  , mFramebuffer(nullptr)
{
}

void ImageOperationHandler::Initialize()
{
  // register for resize event
  CoreModule* core = GetParent()->GetCoreModule();
  Engine* engine = core->GetEngine();
  GraphicsModule* graphics = engine->GetGraphicsModule();
  graphics->RegisterForResize(GlobalKey(), [this](const ResizeEvent& event) { this->Resize(event); });
}

void ImageOperationHandler::Resize(const ResizeEvent& event)
{
  mScreenWidth = static_cast<int>(event.newSize.x);
  mScreenHeight = static_cast<int>(event.newSize.y);
}

void ImageOperationHandler::SetImageA(OpenGLTexture* image)
{
  mImageA = image;
}

void ImageOperationHandler::SetImageB(OpenGLTexture* image)
{
  mImageB = image;
}

void ImageOperationHandler::DoNone()
{
  if (mImageA)
  {
    OpenGLTexture* texture = GetObjectTexture();
    texture->SetImage(mImageA->GetImage(), mImageA->GetWidth(), mImageA->GetHeight());
    texture->RebindTexture();
  }
}

void ImageOperationHandler::DoAddition()
{
  if (mImageA && mImageB)
  {
    OpenGLTexture* texture = GetObjectTexture();
    std::vector<Pixel> addition = GetAddition();
    texture->SetImage(addition, mScreenWidth, mScreenHeight);
    GetParent()->GetComponent<ResizeHandler>()->SetImage(addition, mScreenWidth, mScreenHeight);
    texture->RebindTexture();
  }
}

void ImageOperationHandler::DoSubtraction()
{
  if (mImageA && mImageB)
  {
    OpenGLTexture* texture = GetObjectTexture();
    std::vector<Pixel> subtraction = GetSubtraction();
    texture->SetImage(subtraction, mScreenWidth, mScreenHeight);
    GetParent()->GetComponent<ResizeHandler>()->SetImage(subtraction, mScreenWidth, mScreenHeight);
    texture->RebindTexture();
  }
}

void ImageOperationHandler::DoProduct()
{
  if (mImageA && mImageB)
  {
    OpenGLTexture* texture = GetObjectTexture();
    std::vector<Pixel> product = GetProduct();
    texture->SetImage(product, mScreenWidth, mScreenHeight);
    GetParent()->GetComponent<ResizeHandler>()->SetImage(product, mScreenWidth, mScreenHeight);
    texture->RebindTexture();
  }
}

void ImageOperationHandler::SetImageNegative(int value)
{
  GetFramebuffer()->SetDoImageNegative(value);
}

void ImageOperationHandler::SetLogTransform(int value)
{
  GetFramebuffer()->SetDoLogTransform(value);
}

void ImageOperationHandler::SetGammaTransform(int value)
{
  GetFramebuffer()->SetDoGammaTransform(value);
}

void ImageOperationHandler::SetCValue(float value)
{
  GetFramebuffer()->SetValueC(value);
}

void ImageOperationHandler::SetGammaValue(float value)
{
  GetFramebuffer()->SetValueGamma(value);
}

std::vector<Pixel> ImageOperationHandler::GetAddition()
{
  // Get resized versions
  std::vector<Pixel> imageA;
  std::vector<Pixel> imageB;

  GetResizedImages(imageA, imageB);

  // perform addition
  std::vector<BigPixel> result(imageA.size());

  int max = 0;
  for (int i = 0; i < imageA.size(); i++)
  {
    result[i].r = imageA[i].r + imageB[i].r;
    result[i].g = imageA[i].g + imageB[i].g;
    result[i].b = imageA[i].b + imageB[i].b;
    result[i].a = 255;
    max = std::max<int>(max, std::max<int>(result[i].r, std::max<int>(result[i].g, result[i].b)));
  }

  float ratio = 255.0f / max;
  std::vector<Pixel> normalized(result.size());
  NormalizeImage(result, ratio, normalized);
  return normalized;
}

std::vector<Pixel> ImageOperationHandler::GetSubtraction()
{
  // Get resized versions
  std::vector<Pixel> imageA;
  std::vector<Pixel> imageB;

  GetResizedImages(imageA, imageB);

  // perform subtraction
  std::vector<BigPixel> result(imageA.size());
  int max = 0;
  for (int i = 0; i < imageA.size(); i++)
  {
    result[i].r = imageA[i].r - imageB[i].r;
    result[i].g = imageA[i].g - imageB[i].g;
    result[i].b = imageA[i].b - imageB[i].b;
    result[i].a = 255;
    max = std::max<int>(max, std::max<int>(result[i].r, std::max<int>(result[i].g, result[i].b)));
  }

  float ratio = 255.0f / max;
  std::vector<Pixel> normalized(result.size());
  NormalizeImage(result, ratio, normalized);
  return normalized;
}

std::vector<Pixel> ImageOperationHandler::GetProduct()
{
  // Get resized versions
  std::vector<Pixel> imageA;
  std::vector<Pixel> imageB;

  GetResizedImages(imageA, imageB);

  // perform product
  std::vector<BigPixel> result(imageA.size());
  int max = 0;
  for (int i = 0; i < imageA.size(); i++)
  {
    result[i].r = imageA[i].r * imageB[i].r;
    result[i].g = imageA[i].g * imageB[i].g;
    result[i].b = imageA[i].b * imageB[i].b;
    result[i].a = 255;
    max = std::max<int>(max, std::max<int>(result[i].r, std::max<int>(result[i].g, result[i].b)));
  }

  float ratio = 255.0f / max;
  std::vector<Pixel> normalized(result.size());
  NormalizeImage(result, ratio, normalized);
  return normalized;
}

void ImageOperationHandler::GetResizedImages(std::vector<Pixel>& resizedA,
                                             std::vector<Pixel>& resizedB)
{
  // common size = window size

  // resize image A and image B to common size
  ResizeHandler* resize = GetParent()->GetComponent<ResizeHandler>();
  ResizeHandler::InterpolationMode mode = resize->GetInterpolationMode();

  if (mode == ResizeHandler::InterpolationMode::NearestNeighbor)
  {
    resize->NearestNeighborInterpolation(mImageA->GetImage(), mImageA->GetWidth(), mImageA->GetHeight(), resizedA, mScreenWidth, mScreenHeight);
    resize->NearestNeighborInterpolation(mImageB->GetImage(), mImageB->GetWidth(), mImageB->GetHeight(), resizedB, mScreenWidth, mScreenHeight);
  }
  else
  {
    resize->BilinearInterpolation(mImageA->GetImage(), mImageA->GetWidth(), mImageA->GetHeight(), resizedA, mScreenWidth, mScreenHeight);
    resize->BilinearInterpolation(mImageB->GetImage(), mImageB->GetWidth(), mImageB->GetHeight(), resizedB, mScreenWidth, mScreenHeight);
  }
}

void ImageOperationHandler::NormalizeImage(std::vector<BigPixel>& image, float ratio, std::vector<Pixel>& result)
{
  if (ratio < 1.0f)
  {
    for (int i = 0; i < image.size(); i++)
    {
      result[i].r = static_cast<unsigned char>(image[i].r = static_cast<int>(static_cast<float>(image[i].r) * ratio));
      result[i].g = static_cast<unsigned char>(image[i].g = static_cast<int>(static_cast<float>(image[i].g) * ratio));
      result[i].b = static_cast<unsigned char>(image[i].b = static_cast<int>(static_cast<float>(image[i].b) * ratio));
      result[i].a = 255;
    }
  }
  else
  {
    for (int i = 0; i < image.size(); i++)
    {
      result[i].r = image[i].r;
      result[i].g = image[i].g;
      result[i].b = image[i].b;
      result[i].a = 255;
    }
  }
}

OpenGLTexture* ImageOperationHandler::GetObjectTexture()
{
  Model* model = GetParent()->GetComponent<Model>();
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(model->GetMesh());

  auto it = mesh->GetSubmeshes().begin();

  if (it != mesh->GetSubmeshes().end())
  {
    return it->GetTexture(TextureType::Diffuse);
  }
  return nullptr;
}

OpenGLFramebuffer* ImageOperationHandler::GetFramebuffer()
{
  if (!mFramebuffer)
  {
    CoreModule* core = GetParent()->GetCoreModule();
    GraphicsModule* graphics = core->GetEngine()->GetGraphicsModule();
    OpenGLModule* glModule = static_cast<OpenGLModule*>(graphics);
    mFramebuffer = glModule->GetFramebuffer();
  }
  return mFramebuffer;
}
} // End of Elba namespace
