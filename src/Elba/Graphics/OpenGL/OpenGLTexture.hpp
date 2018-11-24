#pragma once

#include <string>
#include <gl/glew.h>

namespace Elba
{

struct Pixel
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

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

  void GenerateFramebufferTexture();

  void GenerateTexture();
  void DeleteTexture();
  void RebindTexture();

  void Bind(char slot);

  void SetUniform(unsigned int shaderPrg, std::string uniform, char slot);

  void Unbind();

  const std::string& GetPath() const;

  void SaveAsPPM(const std::string& path);

  std::vector<Pixel>& GetImage();
  void SetImage(const std::vector<Pixel>& image, int width, int height);

  int GetWidth() const;
  int GetHeight() const;

  void SetWidth(int width);
  void SetHeight(int height);

  void SetUniformName(std::string name);
  std::string GetUniformName() const;

private:
  std::string mPath;
  std::string mUniformName;

  // gl texture
  GLuint mTexture;
  char mSlot;

  // raw image
  std::vector<Pixel> mRawImage;

  int mWidth;
  int mHeight;
  int mChannels;

  void LoadPPM(std::string path);

  void InsertPPMToken(std::ofstream& file, int token, int& tokenCount);
};

} // End of Elba namespace
