#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

namespace Elba
{
  OpenGLTexture::OpenGLTexture(std::string aPath) : width(0), height(0), channels(0)
  {
    rawImage = stbi_load(aPath.c_str(), &width, &height, &channels, 3);

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rawImage);

    // unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void OpenGLTexture::Bind(char aSlot)
  {
    glActiveTexture(GL_TEXTURE0 + aSlot);
    glBindTexture(GL_TEXTURE_2D, texture);
    slot = aSlot;
  }

  void OpenGLTexture::SetUniform(unsigned int aShaderPrg, std::string aUniform, char aSlot)
  {
    int loc = glGetUniformLocation(aShaderPrg, aUniform.c_str());
    glUniform1i(loc, GL_TEXTURE0 + aSlot);
  }

  void OpenGLTexture::Unbind()
  {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

} // End of Elba namespace
