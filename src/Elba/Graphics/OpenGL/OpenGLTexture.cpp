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
  : mWidth(0), mHeight(0), mChannels(0)
{
}

OpenGLTexture::OpenGLTexture(std::string path, FileType fileType)
  : mWidth(0), mHeight(0), mChannels(0)
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
      mRawImage = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, 3);
      break;
    }

    default:
    {
      throw std::exception("File Type error");
    }
  }

  glGenTextures(1, &mTexture);

  glBindTexture(GL_TEXTURE_2D, mTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mRawImage);

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
  glUniform1i(loc, GL_TEXTURE0 + slot);
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

unsigned char* OpenGLTexture::GetImage()
{
  return mRawImage;
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

    mRawImage = new unsigned char[mWidth * mHeight * 3];

    for (unsigned int i = 4; i < tokens.size(); ++i)
    {
      mRawImage[i] = static_cast<unsigned char>(std::stoi(tokens[i]));
    }
  }
}

} // End of Elba namespace
