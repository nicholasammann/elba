#include <qmenubar.h>

#include "Framework/MainWindow.hpp"
#include "Framework/Workspace.hpp"

namespace Editor
{
namespace Framework
{

MainWindow::MainWindow()
{
  QMainWindow::setMenuBar(new QMenuBar(this));
}

} // End of Framework namespace
} // End of Editor namespace
