#include <gl/glew.h>

#include <qpainter.h>
#include <qopenglpaintdevice.h>
#include <qevent.h>

#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Components/CS370/ResizeHandler.hpp"

#include "Elba/Engine.hpp"

#include "Elba/Graphics/GraphicsModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

#include "Editor/ImageEditor/ImageEditor.hpp"
#include "Editor/ImageEditor/ImageWindow/ImageWindow.hpp"

#include "Elba/Utilities/Utils.hpp"


namespace Editor
{

ImageWindow::ImageWindow(ImageEditor* editor, QWindow* parent)
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

ImageWindow::~ImageWindow()
{
}

void ImageWindow::Render(QPainter* painter)
{
  Q_UNUSED(painter);
}

void ImageWindow::Render()
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

void ImageWindow::Initialize()
{
  glEnable(GL_DEPTH_TEST);

  GLenum err = glewInit();
}

void ImageWindow::SetAnimating(bool animating)
{
  mAnimating = animating;

  if (mAnimating)
  {
    RenderLater();
  }
}

void ImageWindow::RegisterForResize(Elba::GlobalKey key, ResizeCallback callback)
{
  mResizeCallbacks.emplace_back(std::make_pair(key, callback));
}

bool ImageWindow::DeregisterForResize(Elba::GlobalKey key)
{
  auto result = std::find_if(mResizeCallbacks.begin(), mResizeCallbacks.end(),
    [key](const std::pair<Elba::GlobalKey, ResizeCallback>& pair)
  {
    if (key.ToStdString() == pair.first.ToStdString())
    {
      return true;
    }
    return false;
  });

  if (result != mResizeCallbacks.end())
  {
    mResizeCallbacks.erase(result);
    return true;
  }

  return false;
}

void ImageWindow::RenderLater()
{
  requestUpdate();
}

void ImageWindow::RenderNow()
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
    // Test Level
    Elba::CoreModule* core = mEditor->GetEngine()->GetCoreModule();
    Elba::Level* level = core->GetGameLevel();

    Elba::Object* object = level->CreateChild();

    Elba::Transform* transform = object->AddComponent<Elba::Transform>();
    transform->SetWorldTranslation(glm::vec3(0.0f, 0.0f, -10.0f));
    transform->SetWorldRotation(glm::quat(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f)));
    transform->SetWorldScale(glm::vec3(size().width(), 1.0f, size().height()));

    Elba::Model* model = object->AddComponent<Elba::Model>();
    model->LoadMesh("quad.fbx");
    model->LoadShader("textured");

    Elba::OpenGLMesh* mesh = static_cast<Elba::OpenGLMesh*>(model->GetMesh());
    std::vector<Elba::OpenGLSubmesh>& submeshes = mesh->GetSubmeshes();
    std::string assetsDir = Elba::Utils::GetAssetsDirectory();

    std::string texturePath = assetsDir + "Textures/Test_images/apple-20.ppm";

    // add and init ResizeHandler so it receives the TextureChange event
    Elba::ResizeHandler* resizeHandler = object->AddComponent<Elba::ResizeHandler>();
    resizeHandler->Initialize();

    // Load the texture
    for (auto it = submeshes.begin(); it != submeshes.end(); it++)
    {
      Elba::OpenGLTexture* texture = new Elba::OpenGLTexture(texturePath, Elba::OpenGLTexture::FileType::ppm);

      it->LoadTexture(texture);
    }

    ////////////////////////
  }
}

bool ImageWindow::event(QEvent* event)
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

      ResizeEvent resize;
      resize.oldSize = glm::vec2(realEvent->oldSize().width(), realEvent->oldSize().height());
      resize.newSize = glm::vec2(realEvent->size().width(), realEvent->size().height());

      for (auto cb : mResizeCallbacks)
      {
        cb.second(resize);
      }

      return QWindow::event(event);
    }

    default:
    {
      return QWindow::event(event);
    }
  }
}

void ImageWindow::exposeEvent(QExposeEvent* event)
{
  Q_UNUSED(event);

  if (isExposed())
  {
    RenderNow();
  }
}

} // End of Editor namespace
