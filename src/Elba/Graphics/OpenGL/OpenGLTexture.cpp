#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

namespace Elba
{
OpenGLTexture::OpenGLTexture()
  : mWidth(0)
  , mHeight(0)
  , mChannels(0)
{
}

OpenGLTexture::OpenGLTexture(std::string path, FileType fileType)
  : mWidth(0)
  , mHeight(0)
  , mChannels(0)
{
  switch (fileType)
  {
    case FileType::ppm:
    {
      LoadPPM(path);
      break;
    }

    case FileType::other:
    {
      unsigned char* image = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, 3);

      for (int y = 0; y < mHeight; ++y)
      {
        for (int x = 0; x < mWidth; ++x)
        {
          int ind = y * mWidth * 3 + x * 3;

          Pixel pixel;
          pixel.r = image[ind];
          pixel.g = image[ind + 1];
          pixel.b = image[ind + 2];
          pixel.a = 255;

          mRawImage.emplace_back(pixel);
        }
      }

      break;
    }

    default:
    {
      throw std::exception("File Type error");
    }
  }

  mPath = path;

  GenerateTexture();
}

void OpenGLTexture::GenerateFramebufferTexture()
{
  glGenTextures(1, &mTexture);

  // bind
  glBindTexture(GL_TEXTURE_2D, mTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  // unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);
}

void OpenGLTexture::GenerateTexture()
{
  glGenTextures(1, &mTexture);

  // bind
  glBindTexture(GL_TEXTURE_2D, mTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<unsigned char*>(mRawImage.data()));

  // unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture::DeleteTexture()
{
  glDeleteTextures(1, &mTexture);
}

void OpenGLTexture::RebindTexture()
{
  // bind
  glBindTexture(GL_TEXTURE_2D, mTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<unsigned char*>(mRawImage.data()));

  // unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture::Bind(char slot)
{
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, mTexture);
  mSlot = slot;
}

void OpenGLTexture::SetUniform(unsigned int shaderPrg, std::string uniform, char slot)
{
  int loc = glGetUniformLocation(shaderPrg, uniform.c_str());

  if (loc == -1)
  {

  }

  glUniform1i(loc, slot);
}

void OpenGLTexture::Unbind()
{
  glActiveTexture(GL_TEXTURE0 + mSlot);
  glBindTexture(GL_TEXTURE_2D, 0);
}

const std::string& OpenGLTexture::GetPath() const
{
  return mPath;
}

void OpenGLTexture::SaveAsPPM(const std::string& path)
{
  std::ofstream file(path);

  if (file.is_open())
  {
    // header
    file << "P3 \n" << mWidth << " " << mHeight << "\n255 \n";

    unsigned currentLine = 1;

    int tokenCount = 0;

    for (Pixel pixel : mRawImage)
    {
      InsertPPMToken(file, pixel.r, tokenCount);
      InsertPPMToken(file, pixel.g, tokenCount);
      InsertPPMToken(file, pixel.b, tokenCount);
    }
  }

  file.close();
}

std::vector<Pixel>& OpenGLTexture::GetImage()
{
  return mRawImage;
}

void OpenGLTexture::SetImage(const std::vector<Pixel>& image, int width, int height)
{
  mRawImage = image;
  mWidth = width;
  mHeight = height;
}

int OpenGLTexture::GetWidth() const
{
  return mWidth;
}

int OpenGLTexture::GetHeight() const
{
  return mHeight;
}

void OpenGLTexture::SetWidth(int width)
{
  mWidth = width;
}

void OpenGLTexture::SetHeight(int height)
{
  mHeight = height;
}

void OpenGLTexture::SetUniformName(std::string name)
{
  mUniformName = name;
}

std::string OpenGLTexture::GetUniformName() const
{
  return mUniformName;
}

void OpenGLTexture::LoadPPM(std::string path)
{
  // GONNA DO ALL THE PPM LOADING YEEEEEEAAAHHH!!!!
  std::ifstream file(path);

  if (file.is_open())
  {
    std::string line;
    std::vector<std::string> tokens;

    // read in header (first 3 lines)
    while (std::getline(file, line))
    {
      if (!line.empty() && line[0] != '#')
      {
        // width and height of image
        std::istringstream strstream(line);
        tokens.insert(tokens.end(), std::istream_iterator<std::string>{strstream}, std::istream_iterator<std::string>{});
      }
    }

    // if we didn't read at least 4 tokens, it can't be a valid ppm
    // this doesn't check to make sure the header is valid, but eh
    // we can worry about that later
    if (tokens.size() < 4)
    {
      return;
    }

    mWidth = std::stoi(tokens[1]);
    mHeight = std::stoi(tokens[2]);
    mChannels = 3;

    for (unsigned int i = 4; i < tokens.size() - 2; i += 3)
    {
      Pixel pixel;

      pixel.r = std::stoi(tokens[i]);
      pixel.g = std::stoi(tokens[i + 1]);
      pixel.b = std::stoi(tokens[i + 2]);
      pixel.a = 255;

      mRawImage.emplace_back(pixel);
    }
  }

  file.close();
}

void OpenGLTexture::InsertPPMToken(std::ofstream& file, int token, int& tokenCount)
{
  file << token << " ";

  ++tokenCount;

  if (tokenCount % 18 == 0)
  {
    file << "\n";
  }
}

Pixel::Pixel() : r(0), g(0), b(0), a(255)
{
}

Pixel::Pixel(int aR, int aG, int aB, int aA)
  : r(aR), g(aG), b(aB), a(aA)
{
}

} // End of Elba namespace
