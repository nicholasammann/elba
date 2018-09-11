#include <qlayout.h>

#include "Editor/LevelEditor/ObjectBrowser/ObjectBrowser.hpp"
#include "Editor/LevelEditor/ObjectBrowser/ObjectTree.hpp"

namespace Editor
{

ObjectBrowser::ObjectBrowser(Framework::Workspace* workspace)
: Widget(workspace)
{
  mObjectTree = Elba::NewUnique<ObjectTree>(this);
  QGridLayout* layout = new QGridLayout();

  layout->addWidget(mObjectTree.get());

  setLayout(layout);
}

Framework::Widget::DockArea ObjectBrowser::GetDefaultDockArea() const
{
  return DockArea::Left;
}

Framework::Widget::DockArea ObjectBrowser::GetAllowedDockAreas() const
{
  return DockArea::All;
}

} // End of Editor namespace