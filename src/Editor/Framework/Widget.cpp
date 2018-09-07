#include "Framework/Widget.hpp"

namespace Editor
{
namespace Framework
{

Widget::Widget(Workspace* workspace)
: QWidget()
, mWorkspace(workspace)
{
}

Widget::DockArea Widget::GetAllowedDockAreas() const
{
  return DockArea::All;
}

} // End of Framework namespace
} // End of Editor namespace
