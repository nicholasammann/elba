#include <gl/glew.h>

#include <qpainter.h>
#include <qopenglpaintdevice.h>
#include <qevent.h>

#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Components/Rotate.hpp"

#include "Elba/Engine.hpp"

#include "Elba/Graphics/GraphicsModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLPostProcess.hpp"

#include "Editor/LevelEditor/LevelEditor.hpp"
#include "Editor/LevelEditor/LevelWindow/LevelWindow.hpp"

#include "Elba/Utilities/Utils.hpp"


Editor::LevelWindow::LevelWindow(LevelEditor* editor, QWindow* parent)
: QWindow(parent)
, mEditor(editor)
, mAnimating(false)
, mContext(nullptr)
, mDevice(nullptr)
{
  glewExperimental = GL_TRUE;

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

  const qreal retinaScale = devicePixelRatio();
  int screenWidth = retinaScale * width();
  int screenHeight = retinaScale * height();

  glViewport(0, 0, screenWidth, screenHeight);

  mGraphicsModule->Render(screenWidth, screenHeight);

  mDevice->setSize(size());
}

void Editor::LevelWindow::Initialize()
{
  GLenum err = glewInit();

  glEnable(GL_DEPTH_TEST);

  Elba::OpenGLModule* glModule = dynamic_cast<Elba::OpenGLModule*>(mGraphicsModule);
  if (glModule)
  {
    glModule->InitializePostProcessing();
    Elba::OpenGLPostProcess* postProcess = glModule->GetPostProcess();
    postProcess->AddComputeShader("noeffect.comp");
  }
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

  if (needsInitialize)
  {
    // Create objects in level
    Elba::CoreModule* core = mEditor->GetEngine()->GetCoreModule();
    Elba::Level* level = core->GetGameLevel();

    Elba::Object* object = level->CreateChild();

    // Add components
    Elba::Transform* transform = object->AddComponent<Elba::Transform>();
    transform->SetWorldTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
    transform->SetWorldRotation(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)));
    transform->SetWorldScale(glm::vec3(1.0f));

    Elba::Model* model = object->AddComponent<Elba::Model>();
    model->LoadMesh("crysis/nanosuit.obj");
    model->LoadShader("textured");

    Elba::Rotate* rotate = object->AddComponent<Elba::Rotate>();

    // Initialize components
    transform->Initialize();
    model->Initialize();
    rotate->Initialize();
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

    case QEvent::Resize:
    {
      QResizeEvent* realEvent = static_cast<QResizeEvent*>(event);

      Elba::ResizeEvent resize;
      resize.oldSize = glm::vec2(realEvent->oldSize().width(), realEvent->oldSize().height());
      resize.newSize = glm::vec2(realEvent->size().width(), realEvent->size().height());

      mGraphicsModule->OnResize(resize);

      return QWindow::event(event);
    }

    case QEvent::Paint:
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
