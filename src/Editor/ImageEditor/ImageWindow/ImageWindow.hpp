#pragma once

#include <qwindow.h>
#include <qopenglfunctions.h>

#include "Elba/Graphics/GraphicsModule.hpp"
#include "Elba/Utilities/GlobalKey.hpp"

namespace Editor
{

class ImageEditor;

struct ResizeEvent
{
  glm::vec2 oldSize;
  glm::vec2 newSize;
};
typedef std::function<void(const ResizeEvent&)> ResizeCallback;

class ImageWindow : public QWindow, protected QOpenGLFunctions
{
public:
  explicit ImageWindow(ImageEditor* editor, QWindow* parent = nullptr);
  ~ImageWindow();

  virtual void Render(QPainter* painter);
  virtual void Render();

  virtual void Initialize();

  void SetAnimating(bool animating);

  void RegisterForResize(Elba::GlobalKey key, ResizeCallback callback);
  bool DeregisterForResize(Elba::GlobalKey key);
  
public slots:
  void RenderLater();
  void RenderNow();

protected:
  bool event(QEvent* event) override;
  void exposeEvent(QExposeEvent* event) override;

private:
  ImageEditor* mEditor;
  Elba::GraphicsModule* mGraphicsModule;

  bool mAnimating;

  QOpenGLContext* mContext;
  QOpenGLPaintDevice* mDevice;

  std::vector<std::pair<Elba::GlobalKey, ResizeCallback> > mResizeCallbacks;
};

} // End of Editor namespace
