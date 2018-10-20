#include <vector>

#include "Elba/Core/Component.hpp"
#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

namespace Elba
{

class ImageOperationHandler : public Component
{
public:
  ImageOperationHandler(Object* parent);

  void Initialize() final;

  void Resize(int screenWidth, int screenHeight);

  void SetImageA(OpenGLTexture* image);
  void SetImageB(OpenGLTexture* image);

  std::vector<Pixel> GetAddition();
  std::vector<Pixel> GetSubtraction();
  std::vector<Pixel> GetProduct();

private:
  OpenGLTexture* mImageA;
  OpenGLTexture* mImageB;
};

} // End of Elba namespace
