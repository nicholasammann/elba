#include <qfiledialog.h>

#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Components/CS370/ImageOperationHandler.hpp"
#include "Elba/Core/Components/Model.hpp"
#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"
#include "Elba/Utilities/Utils.hpp"

#include "Editor/Framework/Workspace.hpp"
#include "Editor/ImageEditor/Menus/ImageOperationsMenu.hpp"
#include "Editor/ImageEditor/ImageEditor.hpp"


namespace Editor
{

ImageOperationsMenu::ImageOperationsMenu(Framework::Workspace* workspace)
  : Framework::Menu("File", workspace)
{
  AddAction<ImageOperationsMenu>("Select Image A", &ImageOperationsMenu::LoadTextureA, this, "Select Image A for image operations.");
  AddAction<ImageOperationsMenu>("Select Image B", &ImageOperationsMenu::LoadTextureB, this, "Select Image B for image operations.");
}

Elba::OpenGLTexture* ImageOperationsMenu::LoadTexture()
{
  std::string assetsDir = Elba::Utils::GetAssetsDirectory();

  // Construct a file dialog for selecting the correct file
  QString fileName = QFileDialog::getOpenFileName(nullptr,
    tr("Load Texture"), assetsDir.c_str(), tr("PPM (*.ppm)"));

  // make sure the user selected a file
  if (fileName == "")
  {
    return nullptr;
  }

  std::string path = fileName.toLocal8Bit().constData();

  return new Elba::OpenGLTexture(path, Elba::OpenGLTexture::FileType::ppm);
}

Elba::Object* ImageOperationsMenu::GetFirstObject()
{
  ImageEditor* workspace = static_cast<ImageEditor*>(mWorkspace);
  Elba::Engine* engine = workspace->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  Elba::ObjectMap const& children = level->GetChildren();
  auto first = children.begin();
  return first->second.get();
}

void ImageOperationsMenu::LoadTextureA()
{
  // Prompt user to select file, load image file into texture
  Elba::OpenGLTexture* texture = LoadTexture();

  // Get only object in scene
  Elba::Object* object = GetFirstObject();

  Elba::ImageOperationHandler* operHandler = object->GetComponent<Elba::ImageOperationHandler>();
  operHandler->SetImageA(texture);
}

void ImageOperationsMenu::LoadTextureB()
{
  // Prompt user to select file, load image file into texture
  Elba::OpenGLTexture* texture = LoadTexture();

  // Get only object in scene
  Elba::Object* object = GetFirstObject();

  Elba::ImageOperationHandler* operHandler = object->GetComponent<Elba::ImageOperationHandler>();
  operHandler->SetImageB(texture);
}


} // End of Editor namespace

