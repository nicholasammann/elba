#pragma once

#include <string>
#include <gl/glew.h>

namespace Elba
{
  class OpenGLTexture
  {
  public:
    OpenGLTexture(std::string aPath);

    void Bind(char aSlot);

    void SetUniform(unsigned int aShaderPrg, std::string aUniform, char aSlot);

    void Unbind();

  private:

    // gl texture
    unsigned int texture;
    char slot;

    // raw image
    unsigned char *rawImage;

    int width;
    int height;
    int channels;

    unsigned char* GetImage()
    {
      return rawImage;
    }
  };

} // End of Elba namespace
