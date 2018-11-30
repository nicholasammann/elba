#include <cmath>
#include <random>
#include <algorithm>

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
  , mUseHistogramEqualization(false)
  , mFourierMethod(FourierMethod::None)
  , mCurrentImage(CurrentImage::Original)
  , mGaussianMean(0.0f)
  , mGaussianVariance(0.0f)
  , mPa(0.0f)
  , mPb(0.0f)
  , mDeviation(0.0f)
  , mSMax(0.0f)
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

void ResizeHandler::SetFourierMethod(FourierMethod method)
{
  mFourierMethod = method;
  Resize(mScreenWidth, mScreenHeight);
}

void ResizeHandler::SetCurrentImage(CurrentImage image)
{
  mCurrentImage = image;

  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());

  auto it = mesh->GetSubmeshes().begin();

  if (it != mesh->GetSubmeshes().end())
  {
    OpenGLTexture* texture = it->GetTexture(TextureType::Diffuse);
    std::vector<Pixel> imagePixels;
    int w = mMasterHeight;
    int h = mMasterWidth;

    switch (mCurrentImage)
    {
      case CurrentImage::Original:
      {
        imagePixels = mOriginalImage;
        break;
      }

      case CurrentImage::Frequency:
      {
        imagePixels = mFrequencyImage;
        break;
      }

      case CurrentImage::Transformed:
      {
        imagePixels = mTransformedImage;
        break;
      }
    }

    // do some form of interpolation
    switch (mInterpolationMode)
    {
      case InterpolationMode::NearestNeighbor:
      {
        NearestNeighborInterpolation(texture, w, h, imagePixels);
        break;
      }

      case InterpolationMode::Bilinear:
      {
        BilinearInterpolation(texture, w, h, imagePixels);
        break;
      }
    }

    if (mUseHistogramEqualization)
    {
      // do histogram equalization
      HistogramEqualization(imagePixels);
    }

    // update the image on the texture
    texture->SetImage(imagePixels, w, h);

    // bind the new image data to the gpu
    texture->RebindTexture();
  }
}

void ResizeHandler::ApplyGaussianNoise()
{
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());

  auto it = mesh->GetSubmeshes().begin();

  if (it != mesh->GetSubmeshes().end())
  {
    OpenGLTexture* texture = it->GetTexture(TextureType::Diffuse);

    for (int y = 0; y < mNoisyHeight; y++)
    {
      for (int x = 0; x < mNoisyWidth; x++)
      {
        int noise = static_cast<int>(GaussianNoise(x, y));
        int index = IndexAt(x, y, mNoisyWidth);
        mNoisyImage[index].r = std::clamp(mNoisyImage[index].r + noise, 0, 255);
        mNoisyImage[index].g = std::clamp(mNoisyImage[index].g + noise, 0, 255);
        mNoisyImage[index].b = std::clamp(mNoisyImage[index].b + noise, 0, 255);
      }
    }

    // update the image on the texture
    texture->SetImage(mNoisyImage, mNoisyWidth, mNoisyHeight);

    // bind the new image data to the gpu
    texture->RebindTexture();
  }
}

void ResizeHandler::ApplySaltPepperNoise()
{
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());

  auto it = mesh->GetSubmeshes().begin();

  if (it != mesh->GetSubmeshes().end())
  {
    OpenGLTexture* texture = it->GetTexture(TextureType::Diffuse);

    static std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int y = 0; y < mNoisyHeight; y++)
    {
      for (int x = 0; x < mNoisyWidth; x++)
      {
        int index = IndexAt(x, y, mNoisyWidth);
        double noise = distribution(generator);
        if (noise < mPa)
        {
          mNoisyImage[index] = Pixel(0, 0, 0, 255);
        }
        else if (noise > mPb)
        {
          mNoisyImage[index] = Pixel(255, 255, 255, 255);
        }
      }
    }

    // update the image on the texture
    texture->SetImage(mNoisyImage, mNoisyWidth, mNoisyHeight);

    // bind the new image data to the gpu
    texture->RebindTexture();
  }
}

void ResizeHandler::ApplyNoiseReduction()
{
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());

  auto it = mesh->GetSubmeshes().begin();

  if (it != mesh->GetSubmeshes().end())
  {
    OpenGLTexture* texture = it->GetTexture(TextureType::Diffuse);

    static std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int y = 0; y < mNoisyHeight; y++)
    {
      for (int x = 0; x < mNoisyWidth; x++)
      {
        int a = ColorAt(x - 1, y - 1, mNoisyWidth, mNoisyImage);
        int b = ColorAt(x,     y - 1, mNoisyWidth, mNoisyImage);
        int c = ColorAt(x + 1, y - 1, mNoisyWidth, mNoisyImage);
        int d = ColorAt(x - 1, y,     mNoisyWidth, mNoisyImage);
        int e = ColorAt(x,     y,     mNoisyWidth, mNoisyImage);
        int f = ColorAt(x + 1, y,     mNoisyWidth, mNoisyImage);
        int g = ColorAt(x - 1, y + 1, mNoisyWidth, mNoisyImage);
        int h = ColorAt(x,     y + 1, mNoisyWidth, mNoisyImage);
        int i = ColorAt(x + 1, y + 1, mNoisyWidth, mNoisyImage);

        std::vector<int> kernel = { a , b, c, d, e, f, g, h, i };
        std::sort(kernel.begin(), kernel.end());
        int median = kernel[4];
        mNoisyImage[IndexAt(x, y, mNoisyWidth)] = Pixel(median, median, median, 255);
      }
    }

    // update the image on the texture
    texture->SetImage(mNoisyImage, mNoisyWidth, mNoisyHeight);

    // bind the new image data to the gpu
    texture->RebindTexture();
  }
}

void ResizeHandler::ApplyLocalNoiseReduction()
{
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());

  auto it = mesh->GetSubmeshes().begin();

  if (it != mesh->GetSubmeshes().end())
  {
    OpenGLTexture* texture = it->GetTexture(TextureType::Diffuse);

    static std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int y = 0; y < mNoisyHeight; y++)
    {
      for (int x = 0; x < mNoisyWidth; x++)
      {
        int a = ColorAt(x - 1, y - 1, mNoisyWidth, mNoisyImage);
        int b = ColorAt(x, y - 1, mNoisyWidth, mNoisyImage);
        int c = ColorAt(x + 1, y - 1, mNoisyWidth, mNoisyImage);
        int d = ColorAt(x - 1, y, mNoisyWidth, mNoisyImage);
        int e = ColorAt(x, y, mNoisyWidth, mNoisyImage);
        int f = ColorAt(x + 1, y, mNoisyWidth, mNoisyImage);
        int g = ColorAt(x - 1, y + 1, mNoisyWidth, mNoisyImage);
        int h = ColorAt(x, y + 1, mNoisyWidth, mNoisyImage);
        int i = ColorAt(x + 1, y + 1, mNoisyWidth, mNoisyImage);

        std::vector<int> kernel = { a , b, c, d, e, f, g, h, i };

        float mean = (a + b + c + d + e + f + g + h + i) / 9.0f;
        float var = Variance(kernel, mean);

        int col = static_cast<float>(e) - (((mDeviation * mDeviation) / var) * (static_cast<float>(e) - mean));

        mNoisyImage[IndexAt(x, y, mNoisyWidth)] = Pixel(col, col, col, 255);
      }
    }

    // update the image on the texture
    texture->SetImage(mNoisyImage, mNoisyWidth, mNoisyHeight);

    // bind the new image data to the gpu
    texture->RebindTexture();
  }
}

void ResizeHandler::ApplyAdaptiveNoiseReduction()
{
  OpenGLMesh* mesh = static_cast<OpenGLMesh*>(mModel->GetMesh());

  auto it = mesh->GetSubmeshes().begin();

  if (it != mesh->GetSubmeshes().end())
  {
    OpenGLTexture* texture = it->GetTexture(TextureType::Diffuse);

    static std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int y = 0; y < mNoisyHeight; y++)
    {
      for (int x = 0; x < mNoisyWidth; x++)
      {
        int a1 = 0;
        int a2 = 0;
        int n = 3;
        int min = 0;
        int median = 0;
        int max = 0;

        while (n <= mSMax)
        {
          std::vector<int> kernel;
          FindKernel(x, y, n, mNoisyWidth, mNoisyImage, kernel);
          std::sort(kernel.begin(), kernel.end());
          min = kernel.front();
          median = kernel[kernel.size() / 2];
          max = kernel.back();

          a1 = median - min;
          a2 = median - max;

          if (a1 > 0 && a2 < 0)
          {
            break;
          }
          n += 2;
        }

        int col = 0;
        if (n > mSMax)
        {
          col = median;
        }
        // stage B
        else
        {
          int zxy = ColorAt(x, y, mNoisyWidth, mNoisyImage);
          int b1 = zxy - min;
          int b2 = zxy - max;

          if (b1 > 0 && b2 < 0)
          {
            col = zxy;
          }
          else
          {
            col = median;
          }
        }

        mNoisyImage[IndexAt(x, y, mNoisyWidth)] = Pixel(col, col, col, 255);
      }
    }

    // update the image on the texture
    texture->SetImage(mNoisyImage, mNoisyWidth, mNoisyHeight);

    // bind the new image data to the gpu
    texture->RebindTexture();
  }
}

int ResizeHandler::ColorAt(int x, int y, int w, const std::vector<Pixel>& image)
{
  // ASSUME GRAYSCALE
  int index = IndexAt(x, y, w);
  if (index < 0 || index >= image.size())
  {
    return 0;
  }
  return image[index].r;
}

float ResizeHandler::Variance(const std::vector<int>& arr, float mean)
{
  float sum = 0;

  for (int val : arr)
  {
    float diff = static_cast<float>(val) - mean;
    sum += diff * diff;
  }

  return static_cast<float>(sum) / static_cast<float>(arr.size());
}

float ResizeHandler::Mean(const std::vector<int>& arr)
{
  float sum = 0.0f;
  for (int val : arr)
  {
    sum += val;
  }
  return sum / arr.size();
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
      case FourierMethod::None:
      {
        // Do nothing
        break;
      }

      case FourierMethod::DirectMethod:
      {
        DirectFourier(image, w, h);
        break;
      }

      case FourierMethod::SeparableMethod:
      {
        SeparableFourier(image, w, h);
        break;
      }

      case FourierMethod::FastFourier:
      {
        FastFourier(image, w, h);
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

    mNoisyImage = image;
    mNoisyWidth = w;
    mNoisyHeight = h;

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

  return src[static_cast<int>(sY) * width + static_cast<int>(sX)];
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

  int x1 = static_cast<int>(floor(tX));
  int x2 = static_cast<int>(floor(tX + 1));
  
  if (x2 >= width)
  {
    x2 = 0;
  }

  int y1 = static_cast<int>(floor(tY));
  int y2 = static_cast<int>(floor(tY + 1));

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
  result.r = static_cast<unsigned char>((1.0f - beta) * fxy1 + beta * fxy2);

  fxy1 = (1.0f - alpha) * src[y1 * width + x1].g + alpha * src[y1 * width + x2].g;
  fxy2 = (1.0f - alpha) * src[y2 * width + x1].g + alpha * src[y2 * width + x2].g;
  result.g = static_cast<unsigned char>((1.0f - beta) * fxy1 + beta * fxy2);

  fxy1 = (1.0f - alpha) * src[y1 * width + x1].b + alpha * src[y1 * width + x2].b;
  fxy2 = (1.0f - alpha) * src[y2 * width + x1].b + alpha * src[y2 * width + x2].b;
  result.b = static_cast<unsigned char>((1.0f - beta) * fxy1 + beta * fxy2);

  result.a = 255;

  return result;
}

void ResizeHandler::HistogramEqualization(std::vector<Pixel>& image)
{
  size_t total = image.size();

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
    roundedMapping[i] = static_cast<int>(std::round(current));
    prev = current;
  }

  for (Pixel& pixel : image)
  {
    pixel.r = roundedMapping[pixel.r];
    pixel.g = roundedMapping[pixel.g];
    pixel.b = roundedMapping[pixel.b];
  }
}

void ResizeHandler::DirectFourier(std::vector<Pixel>& image, int w, int h)
{
  mOriginalImage = image;

  Fourier::SpatialImage spatialImage;
  CopyToSpatialImage(image, spatialImage, w, h);

  Fourier::FrequencyImage freqImage;
  Fourier::SpatialImage transformed;
  Fourier::Direct(spatialImage, freqImage, transformed);

  CopyFromFrequencyImage(freqImage, mFrequencyImage, w, h);
}

void ResizeHandler::SeparableFourier(std::vector<Pixel>& image, int w, int h)
{
  mOriginalImage = image;

  Fourier::SpatialImage spatialImage;
  CopyToSpatialImage(image, spatialImage, w, h);
  
  Fourier::FrequencyImage freqImage;
  Fourier::SpatialImage transformed;
  Fourier::Separable(spatialImage, freqImage, transformed);

  CopyFromFrequencyImage(freqImage, mFrequencyImage, w, h);
}

void ResizeHandler::FastFourier(std::vector<Pixel>& image, int w, int h)
{
  mOriginalImage = image;

  Fourier::SpatialImage spatialImage;
  CopyToSpatialImage(image, spatialImage, w, h);

  Fourier::FrequencyImage freqImage;
  Fourier::SpatialImage transformed;
  Fourier::Fast(spatialImage, freqImage, transformed);
  
  CopyFromFrequencyImage(freqImage, mFrequencyImage, w, h);
}

void ResizeHandler::CopyToSpatialImage(const std::vector<Pixel>& image, Fourier::SpatialImage& spatial, int w, int h)
{
  spatial.resize(h);

  int index = 0;

  for (int y = 0; y < h; ++y)
  {
    spatial[y].resize(w);
    for (int x = 0; x < w; ++x)
    {
      spatial[y][x] = static_cast<int>(0.3 * image[index].r + 0.59 * image[index].g + 0.11 * image[index].b);
      index++;
    }
  }
}

void ResizeHandler::CopyFromFrequencyImage(const Fourier::FrequencyImage& frequency, std::vector<Pixel>& image, int w, int h)
{
  image.resize(w * h);

  for (int y = 0; y < h; ++y)
  {
    for (int x = 0; x < w; ++x)
    {
      int shiftedY = (y + h / 2) % h;
      int shiftedX = (x + w / 2) % w;
      int index = shiftedY * w + shiftedX;

      int val = static_cast<int>(sqrt(frequency[y][x].real * frequency[y][x].real + frequency[y][x].imaginary * frequency[y][x].imaginary));
      image[index].r = val;
      image[index].g = val;
      image[index].b = val;
      index++;
    }
  }
}

int ResizeHandler::IndexAt(int x, int y, int w)
{
  return y * w + x;
}

float ResizeHandler::GaussianNoise(int x, int y)
{
  //float expX = ((x - mGaussianMeanX) * (x - mGaussianMeanX)) / (2 * mGaussianVarianceX * mGaussianVarianceX);
  //float expY = ((y - mGaussianMeanY) * (y - mGaussianMeanY)) / (2 * mGaussianVarianceY * mGaussianVarianceY);

  static std::default_random_engine generator;
  std::normal_distribution<double> distribution(mGaussianMean, mGaussianVariance);
  return static_cast<float>(distribution(generator));
}

void Elba::ResizeHandler::FindKernel(int x, int y, int n, int w,
  const std::vector<Pixel>& image, std::vector<int>& output)
{
  output.clear();

  int bound = n / 2;

  for (int j = -bound; j <= bound; j++)
  {
    for (int i = -bound; i <= bound; i++)
    {
      output.push_back(ColorAt(x + i, y + j, w, image));
    }
  }
}

void ResizeHandler::SetGaussianMean(float value)
{
  mGaussianMean = value;
}

void ResizeHandler::SetGaussianVariance(float value)
{
  mGaussianVariance = value;
}

void ResizeHandler::SetPa(float value)
{
  mPa = value;
}

void ResizeHandler::SetPb(float value)
{
  mPb = value;
}

void ResizeHandler::SetDeviation(float value)
{
  mDeviation = value;
}

void ResizeHandler::SetSMax(float value)
{
  mSMax = value;
}

} // End of Elba namespace

