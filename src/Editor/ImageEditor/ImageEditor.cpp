#include <qtimer.h>

#include "Elba/Core/CoreModule.hpp"

#include "Editor/ImageEditor/ImageEditor.hpp"
#include "Editor/ImageEditor/ImageWindow/ImageWindow.hpp"
#include "Editor/ImageEditor/Menus/FileMenu.hpp"

namespace Editor
{

ImageEditor::ImageEditor(Framework::MainWindow* mainWindow)
: Workspace(mainWindow)
{
  mEngine = new Elba::Engine(true);

  mEngine->Initialize();

  mImageWindow = new ImageWindow(this);

  QTimer::singleShot(30, [this]()
  {
    Update();
  });
}

bool ImageEditor::Initialize()
{
  QTabWidget* tabs = new QTabWidget();
  tabs->setMovable(true);
  tabs->setTabsClosable(true);
  tabs->setUsesScrollButtons(true);

  Framework::MainWindow* mainWindow = GetMainWindow();

  mainWindow->setCentralWidget(tabs);
  QWidget* container = mainWindow->createWindowContainer(mImageWindow);
  tabs->addTab(container, "Image Window");

  // Add menus
  AddMenu<FileMenu>(this);

  return true;
}

void ImageEditor::Shutdown()
{
}

void ImageEditor::Update()
{
  mEngine->Update();

  mImageWindow->RenderNow();

  QTimer::singleShot(0, [this]()
  {
    Update();
  });
}

Elba::Engine* ImageEditor::GetEngine()
{
  return mEngine;
}

} // End of Editor namespace
