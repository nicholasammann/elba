#pragma once

#include <memory>

#include <qmenu.h>

namespace Editor
{
namespace Framework
{

class MainWindow;

class Menu : public QMenu
{
public:
  Menu(const char* aHeader, MainWindow* mainWindow);

  template<typename T>
  void AddAction(const char* aHeader, void (T::*aFn)(), Menu* aMenu, const char* aTooltip = "");

  void AddMenu(Menu* aMenu);

protected:
  MainWindow* mMainWindow;
};

template<typename T>
void Menu::AddAction(const char* aHeader, void(T::*aFn)(), Menu* aMenu, const char* aTooltip)
{
  QAction* action = new QAction(aHeader);
  addAction(action);
  connect(action, &QAction::triggered, static_cast<T*>(aMenu), aFn);
  action->setToolTip(aTooltip);
}

} // End of Framework namespace
} // End of Editor namespace
