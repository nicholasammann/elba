#include <qpainter.h>
#include <qopenglpaintdevice.h>

#include "Elba/Engine.hpp"
#include "Elba/Graphics/GraphicsModule.hpp"

#include "Editor/LevelEditor/LevelEditor.hpp"
#include "Editor/LevelEditor/LevelWindow/LevelWindow.hpp"

Editor::LevelWindow::LevelWindow(LevelEditor* editor, QWindow* parent)
: QWindow(parent)
, mEditor(editor)
, mAnimating(false)
, mContext(nullptr)
, mDevice(nullptr)
{
  // Cache graphics module for easy use in render fn
  Elba::Engine* engine = mEditor->GetEngine();
  Elba::GraphicsModule* graphicsModule = engine->GetGraphicsModule();
  mGraphicsModule = graphicsModule;

  // Tell the window we're using OpenGL
  setSurfaceType(QWindow::OpenGLSurface);
}

Editor::LevelWindow::~LevelWindow()
{
}

void Editor::LevelWindow::Render(QPainter* painter)
{
  Q_UNUSED(painter);
}

void Editor::LevelWindow::Render()
{
  if (!mDevice)
  {
    mDevice = new QOpenGLPaintDevice();
  }

  mGraphicsModule->Render();

  mDevice->setSize(size());
  QPainter painter(mDevice);
  Render(&painter);
}

void Editor::LevelWindow::Initialize()
{
}

void Editor::LevelWindow::SetAnimating(bool animating)
{
  mAnimating = animating;

  if (mAnimating)
  {
    RenderLater();
  }
}

void Editor::LevelWindow::RenderLater()
{
  requestUpdate();
}

void Editor::LevelWindow::RenderNow()
{
  if (!isExposed())
  {
    return;
  }

  bool needsInitialize = false;
  
  if (!mContext)
  {
    mContext = new QOpenGLContext(this);
    mContext->setFormat(requestedFormat());
    mContext->create();

    needsInitialize = true;
  }

  mContext->makeCurrent(this);
  
  if (needsInitialize)
  {
    initializeOpenGLFunctions();
    Initialize();
  }

  Render();

  mContext->swapBuffers(this);

  if (mAnimating)
  {
    RenderLater();
  }
}

bool Editor::LevelWindow::event(QEvent* event)
{
  switch (event->type())
  {
    case QEvent::UpdateRequest:
    {
      RenderNow();
      return true;
    }

    default:
    {
      return QWindow::event(event);
    }
  }
}

void Editor::LevelWindow::exposeEvent(QExposeEvent* event)
{
  Q_UNUSED(event);

  if (isExposed())
  {
    RenderNow();
  }
}
