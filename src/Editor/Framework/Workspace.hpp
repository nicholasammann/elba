#pragma once

#include <map>
#include <typeindex>
#include <memory>

#include <qdockwidget.h>

#include "Framework/MainWindow.hpp"
#include "Framework/Menu.hpp"
#include "Framework/ToolBar.hpp"
#include "Framework/Widget.hpp"

namespace Editor
{
namespace Framework
{

class MainWindow;

/**
* Base class for defining a toolset of custom widgets
*/
class Workspace
{
public:
  Workspace(MainWindow* mainWindow);

  virtual bool Initialize() = 0;
  virtual void Shutdown() = 0;

  /**
  * Returns first pointer of given type
  */
  template <typename T>
  T* GetWidget() const;

  /**
  * Returns all pointers of given type
  */
  template <typename T>
  std::vector<T*> GetAllWidgets() const;

  /**
  * Returns the MainWindow handling the workspace
  */
  MainWindow* GetMainWindow() const;

protected:
  /**
  * Creates a widget of given type
  * Returns pointer to created widget
  */
  template <typename T, typename... Args>
  T* LoadWidget(Args&&... args);

  /**
  * Unloads one instance of a type of widget
  * Returns true if an instance is unloaded, false if no instance of given type is found
  */
  template <typename T>
  bool UnloadWidget(T* widget);

  /**
  * Unload all instances of a type of widget
  * Returns number of instances unloaded
  */
  template <typename T>
  size_t UnloadWidgets();

  /**
  * Creates a toolbar of given type
  * Returns pointer to created toolbar
  */
  template <typename T, typename... Args>
  T* LoadToolBar(Args&&... args);

  /**
  * Unloads one instance of a type of toolbar
  * Returns true if an instance is unloaded, false if no instance of given type is found
  */
  template <typename T>
  bool UnloadToolBar(T* widget);

  /**
  * Unload all instances of a type of toolbar
  * Returns number of instances unloaded
  */
  template <typename T>
  size_t UnloadToolBars();

  /**
  * Creates a menu of given type
  * Returns pointer to created menu
  */
  template <typename T, typename... Args>
  T* LoadMenu(Args&&... args);

  /**
  * Unloads the menu specified by type
  * Returns true if menu is unloaded, false if menu is not found
  */
  template <typename T>
  bool UnloadMenu(T* menu);

private:
  friend class MainWindow;
  MainWindow* mMainWindow;

  // Widgets
  std::multimap<std::type_index, std::unique_ptr<Widget> > mWidgets;

  // Toolbars
  std::multimap<std::type_index, std::unique_ptr<ToolBar> > mToolBars;

  // Menus
  std::map<std::type_index, std::unique_ptr<Menu> > mMenus;
};


// Function Definitions //

template <typename T>
T* Workspace::GetWidget() const
{
  auto it = mWidgets.find(std::type_index(typeid(T)));

  if (it != mWidgets.end())
  {
    return it->second.get();
  }

  return nullptr;
}

template <typename T>
std::vector<T*> Workspace::GetAllWidgets() const
{
  std::vector<T*> result;

  auto range = mWidgets.equal_range(std::type_index(typeid(T)));

  for (auto it = range.first; it != range.second; it++)
  {
    result.emplace_back(it->second.get());
  }

  return result;
}

template <typename T, typename... Args>
T* Workspace::LoadWidget(Args&&... args)
{
  // Create Widget
  std::multimap<std::type_index, std::unique_ptr<Widget> >::iterator inserted = mWidgets.emplace(std::type_index(typeid(T)), std::make_unique<T>(std::forward<Args>(args)...));

  T* widget = static_cast<T*>(inserted->second.get());

  // Create dock to hold widget
  widget->mDockWidget = std::make_unique<QDockWidget>();
  widget->mDockWidget->setAllowedAreas(static_cast<Qt::DockWidgetArea>(widget->GetAllowedDockAreas()));

  // Tell dock what widget it's holding
  widget->mDockWidget->setWidget(widget);

  // Add dock to main window
  mMainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(widget->GetDefaultDockArea()), widget->mDockWidget.get());
  return widget;
}

template <typename T>
bool Workspace::UnloadWidget(T* widget)
{
  auto range = mWidgets.equal_range(std::type_index(typeid(T)));

  for (auto it = range.first; it != range.second; ++it)
  {
    if (it->get() == widget)
    {
      mWidgets.erase(it);
      return true;
    }
  }

  return false;
}

template <typename T>
size_t Workspace::UnloadWidgets()
{
  return mWidgets.erase(std::type_index(typeid(T)));
}

template <typename T, typename... Args>
T* Workspace::LoadToolBar(Args&&... args)
{
  // Create ToolBar
  auto inserted = mToolBars.emplace({ std::type_index(typeid(T)), std::make_unique<T>(std::forward<Args>(args)...) });

  // Add ToolBar to MainWindow
  mMainWindow->addToolBar(inserted->get());
  return inserted->get();
}

template <typename T>
bool Workspace::UnloadToolBar(T* toolbar)
{
  auto range = mToolBars.equal_range(std::type_index(typeid(T)));

  for (auto it = range.first; it != range.second; ++it)
  {
    if (it->get() == toolbar)
    {
      mToolBars.erase(it);
      return true;
    }
  }

  return false;
}

template <typename T>
size_t Workspace::UnloadToolBars()
{
  return mToolBars.erase(std::type_index(typeid(T)));
}

template <typename T, typename... Args>
T* Workspace::LoadMenu(Args&&... args)
{
  // Create Menu
  auto inserted = mMenus.emplace({ std::type_index(typeid(T)), std::make_unique<T>(std::forward<Args>(args)...) });

  // Add ToolBar to MainWindow
  QMenuBar* menuBar = mMainWindow->menuBar();
  menuBar->addMenu(inserted->get());

  return inserted->get();
}

template <typename T>
bool Workspace::UnloadMenu(T* menu)
{
  return mMenus.erase(std::type_index(typeid(T))) > 0;
}

} // End of Framework namespace
} // End of Editor namespace