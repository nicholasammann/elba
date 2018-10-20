#include "Elba/Core/Components/CS370/ImageOperationHandler.hpp"

namespace Elba
{
ImageOperationHandler::ImageOperationHandler(Object* parent) 
  : Component(parent)
{
}

void ImageOperationHandler::Initialize()
{
}

void ImageOperationHandler::Resize(int screenWidth, int screenHeight)
{
}

void ImageOperationHandler::SetImageA(OpenGLTexture* image)
{
  mImageA = image;
}

void ImageOperationHandler::SetImageB(OpenGLTexture* image)
{
  mImageB = image;
}

std::vector<Pixel> ImageOperationHandler::GetAddition()
{
  return std::vector<Pixel>();
}

std::vector<Pixel> ImageOperationHandler::GetSubtraction()
{
  return std::vector<Pixel>();
}

std::vector<Pixel> ImageOperationHandler::GetProduct()
{
  return std::vector<Pixel>();
}
} // End of Elba namespace
