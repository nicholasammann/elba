#pragma once

#include <qwindow.h>
#include <qopenglfunctions.h>

#include "Elba/Graphics/GraphicsModule.hpp"

namespace Editor
{

class ImageEditor;

class ImageWindow : public QWindow, protected QOpenGLFunctions
{
public:
  explicit ImageWindow(ImageEditor* editor, QWindow* parent = nullptr);
  ~ImageWindow();

  virtual void Render(QPainter* painter);
  virtual void Render();

  virtual void Initialize();

  void SetAnimating(bool animating);

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
};

} // End of Editor namespace
