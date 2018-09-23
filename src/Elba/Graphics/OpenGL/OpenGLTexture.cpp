#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

namespace Elba
{
  OpenGLTexture::OpenGLTexture(std::string path) : mWidth(0), mHeight(0), mChannels(0)
  {
    mRawImage = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, 3);

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

} // End of Elba namespace
