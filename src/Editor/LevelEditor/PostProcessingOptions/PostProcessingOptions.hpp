#pragma once

#include <qtreewidget.h>

#include "Editor/Framework/Widget.hpp"

namespace Editor
{

class PostProcessingOptions : public Framework::Widget
{
public:
  PostProcessingOptions(Framework::Workspace* workspace);

  Framework::Widget::DockArea GetDefaultDockArea() const final;
  Framework::Widget::DockArea GetAllowedDockAreas() const final;

private:

  QTreeWidget* mTree;
  void OnContextMenu(const QPoint& point);
  //void OnUsePostProcessingChanged(int value);
};

} // End of Editor namespace

