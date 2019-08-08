#include <qtimer.h>

#include "Elba/Core/CoreModule.hpp"
#include "Elba/GameLogic/CS370/ResizeHandler.hpp"

#include "Editor/ImageEditor/ImageEditor.hpp"
#include "Editor/ImageEditor/ImageWindow/ImageWindow.hpp"
#include "Editor/ImageEditor/Menus/FileMenu.hpp"
#include "Editor/ImageEditor/Menus/ImageOperationsMenu.hpp"
#include "Editor/ImageEditor/OptionsPanel/OptionsPanel.hpp"
#include "Editor/ImageEditor/ImageOperationsPanel/ImageOperationsPanel.hpp"

namespace Editor
{

ImageEditor::ImageEditor(Framework::MainWindow* mainWindow)
: Workspace(mainWindow)
{
  mEngine = new Elba::Engine(true);
  mEngine->Initialize();

  Elba::OpenGLModule* graphics = static_cast<Elba::OpenGLModule*>(mEngine->GetGraphicsModule());
  graphics->GetCamera()->SetProjectionMode(Elba::Camera::ProjectionMode::Orthographic);

  mImageWindow = new ImageWindow(this);

  mResizeCallbackKey = Elba::GlobalKey();
  graphics->RegisterForResize(mResizeCallbackKey, [this](const Elba::ResizeEvent& event)
  {
    this->OnResize(event);
  });

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
  AddMenu<ImageOperationsMenu>(this);

  // Add widgets
  AddWidget<OptionsPanel>(this);
  AddWidget<ImageOperationsPanel>(this);

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

void ImageEditor::OnResize(const Elba::ResizeEvent& event)
{
  Elba::CoreModule* core = mEngine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  Elba::ObjectMap const& children = level->GetChildren();
  auto first = children.begin();

  if (first != children.end())
  {
    Elba::Object* object = first->second.get();
  
    Elba::ResizeHandler* resizeHandler = object->GetComponent<Elba::ResizeHandler>();
    resizeHandler->Resize(static_cast<int>(event.newSize.x), static_cast<int>(event.newSize.y));
  }
}

} // End of Editor namespace
