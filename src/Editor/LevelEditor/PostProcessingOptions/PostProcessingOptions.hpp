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

  void OnUsePostProcessingChanged(int value);
  void OnEdgeDetectionChanged(int value);
  void OnBlurChanged(int value);

  QTreeWidget* mPostProcessingTree;
};

} // End of Editor namespace

