#pragma once

#include <vector>

#include <qtreewidget.h>

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLComputeShader.hpp"

#include "Editor/Framework/Widget.hpp"

namespace Editor
{

class EffectItemWidget;

class PostProcessingOptions : public Framework::Widget
{
public:
  PostProcessingOptions(Framework::Workspace* workspace);

  Framework::Widget::DockArea GetDefaultDockArea() const final;
  Framework::Widget::DockArea GetAllowedDockAreas() const final;

  EffectItemWidget* AddItem(QString header, Elba::OpenGLComputeShader* shader);

  QTreeWidget* GetTree();

  std::vector<Elba::GlobalKey> mMotionBlurKeys;

private:
  QTreeWidget* mTree;
  void OnContextMenu(const QPoint& point);
  void OnUseHatchingChanged(int value);
  void OnLightIntensityChanged(const QString& value);

  // Video options
  void OnTransitionToRealTime();
  void OnTransitionToStaticImage();
  void OnTransitionModeChanged(int value);

  // object movement
  void OnMoveSpeedChanged(const QString& value);
  void OnRotateSpeedChanged(const QString& value);
};

} // End of Editor namespace

