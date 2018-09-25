#include <qfiledialog.h>

#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Components/Model.hpp"
#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"
#include "Elba/Utilities/Utils.hpp"

#include "Editor/Framework/Workspace.hpp"
#include "Editor/ImageEditor/Menus/FileMenu.hpp"
#include "Editor/ImageEditor/ImageEditor.hpp"


namespace Editor
{

FileMenu::FileMenu(Framework::Workspace* workspace)
  : Framework::Menu("File", workspace)
{
  AddAction<FileMenu>("Load Texture", &FileMenu::LoadTexture, this, "Load a texture to be displayed in the image window.");
}

void FileMenu::LoadTexture()
{
  std::string assetsDir = Elba::Utils::GetAssetsDirectory();

  // Construct a file dialog for selecting the correct file
  QString fileName = QFileDialog::getOpenFileName(this,
    tr("Load Texture"), assetsDir.c_str(), tr("All Files (*.*)"));

  // make sure the user selected a file
  if (fileName == "")
  {
    return;
  }

  ImageEditor* workspace = static_cast<ImageEditor*>(mWorkspace);

  Elba::Engine* engine = workspace->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  Elba::ObjectMap const& children = level->GetChildren();
  auto first = children.begin();
  Elba::Object* object = first->second.get();

  Elba::Model* model = object->GetComponent<Elba::Model>();
  Elba::OpenGLMesh* mesh = static_cast<Elba::OpenGLMesh*>(model->GetMesh());
  std::vector<Elba::OpenGLSubmesh>& submeshes = mesh->GetSubmeshes();

  std::string path = fileName.toLocal8Bit().constData();

  Elba::OpenGLTexture* texture = new Elba::OpenGLTexture(path, Elba::OpenGLTexture::FileType::ppm);
  submeshes.begin()->LoadTexture(texture);
}


} // End of Editor namespace

