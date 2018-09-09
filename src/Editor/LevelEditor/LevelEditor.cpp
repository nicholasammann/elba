#include <qtimer.h>

#include "Editor/LevelEditor/LevelEditor.hpp"
#include "Editor/LevelEditor/LevelWindow/LevelWindow.hpp"
#include "Editor/LevelEditor/ObjectBrowser/ObjectBrowser.hpp"

namespace Editor
{

LevelEditor::LevelEditor(Framework::MainWindow* mainWindow)
: Workspace(mainWindow)
{
  mEngine = new Elba::Engine(true);

  mEngine->Initialize();
  
  QTimer::singleShot(0, [this]()
  {
    Update();
  });

  mLevelWindow = new LevelWindow(this);
}

bool LevelEditor::Initialize()
{
  QTabWidget* tabs = new QTabWidget();
  tabs->setMovable(true);
  tabs->setTabsClosable(true);
  tabs->setUsesScrollButtons(true);

  Framework::MainWindow* mainWindow = GetMainWindow();

  mainWindow->setCentralWidget(tabs);
  QWidget* container = mainWindow->createWindowContainer(mLevelWindow);
  tabs->addTab(container, "Level Window");

  LoadWidget<ObjectBrowser>(this);

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

Elba::Engine* LevelEditor::GetEngine()
{
  return mEngine;
}

} // End of Editor namespace
