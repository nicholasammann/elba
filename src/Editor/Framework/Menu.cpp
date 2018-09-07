#include "Framework/Menu.hpp"

namespace Editor
{
namespace Framework
{

Menu::Menu(const char* aHeader, MainWindow* aMainWindow)
  : QMenu(aHeader), mMainWindow(aMainWindow)
{
  setToolTipsVisible(true);
}

void Menu::AddMenu(Menu * aMenu)
{
  addMenu(aMenu);
}

} // End of Framework namespace
} // End of Editor namespace
