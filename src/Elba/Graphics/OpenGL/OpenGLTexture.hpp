#pragma once

#include <string>
#include <gl/glew.h>

namespace Elba
{
class OpenGLTexture
{
public:
  OpenGLTexture();
  OpenGLTexture(std::string path);

  void Bind(char slot);

  void SetUniform(unsigned int shaderPrg, std::string uniform, char slot);

  void Unbind();

  const std::string& GetPath() const;

private:

  std::string mPath;

  // gl texture
  unsigned int mTexture;
  char mSlot;

  // raw image
  unsigned char* mRawImage;

  int mWidth;
  int mHeight;
  int mChannels;

  unsigned char* GetImage()
  {
    return mRawImage;
  }
};

} // End of Elba namespace
