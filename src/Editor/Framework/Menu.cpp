#include "Framework/Menu.hpp"

namespace Editor
{
namespace Framework
{

Menu::Menu(const char* header, Workspace* workspace)
  : QMenu(header), mWorkspace(workspace)
{
  setToolTipsVisible(true);
}

void Menu::AddMenu(Menu* menu)
{
  addMenu(menu);
}

} // End of Framework namespace
} // End of Editor namespace
