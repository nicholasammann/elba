#include <qtimer.h>

#include "Editor/LevelEditor/LevelEditor.hpp"

namespace Editor
{

LevelEditor::LevelEditor(Framework::MainWindow* mainWindow)
: Workspace(mainWindow)
{
  mEngine = new Elba::Engine();

  mEngine->Initialize();
  
  QTimer::singleShot(0, [this]()
  {
    Update();
  });
}

bool LevelEditor::Initialize()
{
  return true;
}

void LevelEditor::Shutdown()
{
}

void LevelEditor::Update()
{
  mEngine->Update();

  QTimer::singleShot(0, [this]()
  {
    Update();
  });
}

} // End of Editor namespace
