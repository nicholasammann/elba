#include "Framework/Workspace.hpp"

namespace Editor
{
namespace Framework
{

Workspace::Workspace(MainWindow* mainWindow)
: mMainWindow(mainWindow)
{
}

MainWindow* Workspace::GetMainWindow() const
{
  return mMainWindow;
}

} // End of Framework namespace
} // End of Editor namespace
