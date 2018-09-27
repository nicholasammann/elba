#pragma once

#include <string>
#include <gl/glew.h>

namespace Elba
{
class OpenGLTexture
{
public:
  enum FileType
  {
    ppm,
    other
  };

  OpenGLTexture();
  OpenGLTexture(std::string path, FileType fileType = FileType::other);

  void GenerateTexture();
  void DeleteTexture();
  void RebindTexture();

  void Bind(char slot);

  void SetUniform(unsigned int shaderPrg, std::string uniform, char slot);

  void Unbind();

  const std::string& GetPath() const;

  void SaveAsPPM(const std::string& path);

  unsigned char* GetImage();
  void SetImage(unsigned char* image, int width, int height);

  int GetWidth() const;
  int GetHeight() const;

private:
  std::string mPath;

  // gl texture
  GLuint mTexture;
  char mSlot;

  // raw image
  unsigned char* mRawImage;

  int mWidth;
  int mHeight;
  int mChannels;

  void LoadPPM(std::string path);
};

} // End of Elba namespace
