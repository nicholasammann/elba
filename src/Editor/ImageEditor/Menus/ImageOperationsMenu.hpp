#pragma once

#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

#include "Editor/Framework/Menu.hpp"

namespace Editor
{

class ImageOperationsMenu : public Framework::Menu
{
public:
  ImageOperationsMenu(Framework::Workspace* workspace);

private:
  Elba::OpenGLTexture* LoadTexture();
  Elba::Object* GetFirstObject();

  void LoadTextureA();
  void LoadTextureB();

};

} // End of Editor namespace

