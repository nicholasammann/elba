#pragma once

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

private:

  QTreeWidget* mTree;
  void OnContextMenu(const QPoint& point);
  void OnUseHatchingChanged(int value);
};

} // End of Editor namespace

