#include <cmath>

#include "Elba/Core/Object.hpp"
#include "Elba/Core/Components/CS370/ResizeHandler.hpp"

#include "Elba/Core/Components/Model.hpp"
#include "Elba/Core/Components/Transform.hpp"

#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"

namespace Elba
{

ResizeHandler::ResizeHandler(Object* parent)
  : Component(parent)
  , mTransform(nullptr)
  , mModel(nullptr)
  , mInterpolationMode(InterpolationMode::None)
  , mMasterWidth(800)
  , mMasterHeight(600)
  , mScreenWidth(800)
  , mScreenHeight(600)
  , mUseHistogramEqualization(true)
{
}

void ResizeHandler::Initialize()
{
  mTransform = GetParent()->GetComponent<Transform>();
  mModel = GetParent()->GetComponent<Model>();

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

ResizeHandler::InterpolationMode ResizeHandler::GetInterpolationMode() const
{
  return mInterpolationMode;
}

void ResizeHandler::NearestNeighborInterpolation(std::vector<Pixel>& source, int srcWidth, int srcHeight, 
                                                 std::vector<Pixel>& result, int targetWidth, int targetHeight)
{
  int stride = targetWidth * 4;

  float widthRatio = static_cast<float>(srcWidth) / static_cast<float>(targetWidth);
  float heightRatio = static_cast<float>(srcHeight) / static_cast<float>(targetHeight);

  for (int y = 0; y < targetHeight; ++y)
  {
    for (int x = 0; x < targetWidth; ++x)
    {
      // bilinear interpolation
      result.emplace_back(NearestNeighborValue(x, y, srcWidth, srcHeight, widthRatio, heightRatio, source));
    }
  }
}

void ResizeHandler::BilinearInterpolation(std::vector<Pixel>& source, int srcWidth, int srcHeight, 
                                          std::vector<Pixel>& result, int targetWidth, int targetHeight)
{
  int stride = targetWidth * 4;

  float widthRatio = static_cast<float>(srcWidth) / static_cast<float>(targetWidth);
  float heightRatio = static_cast<float>(srcHeight) / static_cast<float>(targetHeight);

  for (int y = 0; y < targetHeight; ++y)
  {
    for (int x = 0; x < targetWidth; ++x)
    {
      // bilinear interpolation
      result.emplace_back(BilinearValue(x, y, srcWidth, srcHeight, widthRatio, heightRatio, source));
    }
  }
}

void ResizeHandler::SetImage(const std::vector<Pixel>& image, int width, int height)
{
  mMasterWidth = width;
  mMasterHeight = height;

  // delete old master image
  mMasterImage.clear();

  // allocate new master image
  mMasterImage = image;
}

void ResizeHandler::SetUseHistogramEqualization(bool useHistogram)
{
  mUseHistogramEqualization = useHistogram;
  Interpolate(mScreenWidth, mScreenHeight);
}

void ResizeHandler::UseFourierTransform(Fourier method)
{
}

void ResizeHandler::OnTextureChange(const TextureChangeEvent& event)
{
  mMasterWidth = event.newTexture->GetWidth();
  mMasterHeight = event.newTexture->GetHeight();

  // delete old master image
  mMasterImage.clear();

  // allocate new master image
  mMasterImage = event.newTexture->GetImage();
}

void ResizeHandler::Interpolate(int screenWidth, int screenHeight)
{
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());

  auto it = mesh->GetSubmeshes().begin();

  if (it != mesh->GetSubmeshes().end())
  {
    OpenGLTexture* texture = it->GetTexture(TextureType::Diffuse);
    std::vector<Pixel> image;
    int w = screenWidth;
    int h = screenHeight;

    // do some form of interpolation
    switch (mInterpolationMode)
    {
      case InterpolationMode::NearestNeighbor:
      {
        NearestNeighborInterpolation(texture, screenWidth, screenHeight, image);
        break;
      }

      case InterpolationMode::Bilinear:
      {
        BilinearInterpolation(texture, screenWidth, screenHeight, image);
        break;
      }

      case InterpolationMode::None:
      {
        // EVERYTHING IS AWFUL NO INTERPOLATION OH MY GOD
        image = mMasterImage;
        w = mMasterWidth;
        h = mMasterHeight;
        break;
      }
    }

    // DO THE FOURIER THING OMG
    switch (mFourierMethod)
    {
      case Fourier::None:
      {
        // Do nothing
        break;
      }

      case Fourier::DirectMethod:
      {
        DirectFourier(image);
        break;
      }

      case Fourier::SeparableMethod:
      {
        SeparableFourier(image);
        break;
      }

      case Fourier::FastFourier:
      {
        FastFourier(image);
        break;
      }
    }

    if (mUseHistogramEqualization)
    {
      // do histogram equalization
      HistogramEqualization(image);
    }

    // update the image on the texture
    texture->SetImage(image, w, h);

    // bind the new image data to the gpu
    texture->RebindTexture();
  }
}

void ResizeHandler::NearestNeighborInterpolation(OpenGLTexture* texture, 
                                                 int screenWidth, 
                                                 int screenHeight, 
                                                 std::vector<Pixel>& result)
{
  int stride = screenWidth * 4;

  float widthRatio = static_cast<float>(mMasterWidth) / static_cast<float>(screenWidth);
  float heightRatio = static_cast<float>(mMasterHeight) / static_cast<float>(screenHeight);

  for (int y = 0; y < screenHeight; ++y)
  {
    for (int x = 0; x < screenWidth; ++x)
    {
      // bilinear interpolation
      result.emplace_back(NearestNeighborValue(x, y, mMasterWidth, mMasterHeight, widthRatio, heightRatio, mMasterImage));
    }
  }
}

Pixel ResizeHandler::NearestNeighborValue(int x, int y, int width, int height, float widthRatio, float heightRatio, std::vector<Pixel>& src)
{
  float tX = x * widthRatio;
  float tY = y * heightRatio;

  float sX = roundf(tX);
  float sY = roundf(tY);

  while (sX >= width)
  {
    sX -= width;
  }

  while (sY >= height)
  {
    sY -= height;
  }

  return src[sY * width + sX];
}

void ResizeHandler::BilinearInterpolation(OpenGLTexture* texture, int screenWidth, int screenHeight, std::vector<Pixel>& result)
{
  int stride = screenWidth * 4;

  float widthRatio = static_cast<float>(mMasterWidth) / static_cast<float>(screenWidth);
  float heightRatio = static_cast<float>(mMasterHeight) / static_cast<float>(screenHeight);

  for (int y = 0; y < screenHeight; ++y)
  {
    for (int x = 0; x < screenWidth; ++x)
    {
      // bilinear interpolation
      result.emplace_back(BilinearValue(x, y, mMasterWidth, mMasterHeight, widthRatio, heightRatio, mMasterImage));
    }
  }
}

Pixel ResizeHandler::BilinearValue(int x, int y, int width, int height, float widthRatio, float heightRatio, std::vector<Pixel>& src)
{
  Pixel result;

  float tX = x * widthRatio;
  float tY = y * heightRatio;

  int x1 = floor(tX);
  int x2 = floor(tX + 1);
  
  if (x2 >= width)
  {
    x2 = 0;
  }

  int y1 = floor(tY);
  int y2 = floor(tY + 1);

  if (y2 >= height)
  {
    y2 = 0;
  }

  // alpha = (x - x1) / (x2 - x1)
  // beta = (y - y1) / (y2 - y1)
  // f(x, y1) = (1 - alpha) * f(x1, y1) + alpha * f(x2, y1)
  // f(x, y2) = (1 - alpha) * f(x1, y2) + alpha * f(x2, y2)
  // f(x,y) = (1 - beta) * f(x, y1) + beta * f(x, y2)

  float alpha = (tX - x1) / (x2 - x1);
  float beta = (tY - y1) / (y2 - y1);
  float fxy1 = (1.0f - alpha) * src[y1 * width + x1].r + alpha * src[y1 * width + x2].r;
  float fxy2 = (1.0f - alpha) * src[y2 * width + x1].r + alpha * src[y2 * width + x2].r;
  result.r = (1.0f - beta) * fxy1 + beta * fxy2;

  fxy1 = (1.0f - alpha) * src[y1 * width + x1].g + alpha * src[y1 * width + x2].g;
  fxy2 = (1.0f - alpha) * src[y2 * width + x1].g + alpha * src[y2 * width + x2].g;
  result.g = (1.0f - beta) * fxy1 + beta * fxy2;

  fxy1 = (1.0f - alpha) * src[y1 * width + x1].b + alpha * src[y1 * width + x2].b;
  fxy2 = (1.0f - alpha) * src[y2 * width + x1].b + alpha * src[y2 * width + x2].b;
  result.b = (1.0f - beta) * fxy1 + beta * fxy2;

  result.a = 255;

  return result;
}

void ResizeHandler::HistogramEqualization(std::vector<Pixel>& image)
{
  int total = image.size();

  // first pass to count intensities
  int redHgram[256] = { 0 };
  int blueHgram[256] = { 0 };
  int greenHgram[256] = { 0 };

  for (Pixel& pixel : image)
  {
    ++redHgram[pixel.r];
    ++blueHgram[pixel.g];
    ++greenHgram[pixel.b];
  }

  // second pass to calculate probabilities
  float probs[256] = { 0.0f };
  for (int i = 0; i < 256; ++i)
  {
    //probs[i] = static_cast<float>((redHgram[i] + blueHgram[i] + greenHgram[i])) / (3.0f * total);
    probs[i] = static_cast<float>(redHgram[i]) / total;
  }

  int roundedMapping[256] = { 0 };
  float prev = 0.0f;

  for (int i = 0; i < 256; ++i)
  {
    float current = 255.0f * probs[i] + prev;
    roundedMapping[i] = std::round(current);
    prev = current;
  }

  for (Pixel& pixel : image)
  {
    pixel.r = roundedMapping[pixel.r];
    pixel.g = roundedMapping[pixel.g];
    pixel.b = roundedMapping[pixel.b];
  }
}

} // End of Elba namespace

