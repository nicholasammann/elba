#pragma once

#include <qwindow.h>
#include <qopenglfunctions.h>

#include "Elba/Graphics/GraphicsModule.hpp"

namespace Editor
{

class LevelEditor;

class LevelWindow : public QWindow, protected QOpenGLFunctions
{
public:
  explicit LevelWindow(LevelEditor* editor, QWindow* parent = nullptr);
  ~LevelWindow();

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
  LevelEditor* mEditor;
  Elba::GraphicsModule* mGraphicsModule;

  bool mAnimating;

  QOpenGLContext* mContext;
  QOpenGLPaintDevice* mDevice;
};

} // End of Editor namespace
