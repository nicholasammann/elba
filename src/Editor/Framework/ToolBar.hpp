#pragma once

#include <memory>

#include <qtoolbar.h>

namespace Editor
{
namespace Framework
{

class Workspace;

class ToolBar : public QToolBar
{
public:
  ToolBar(Workspace* workspace);

  template <typename T>
  T* GetWorkspace() const;

private:
  friend class Workspace;
  Workspace* mWorkspace;
};

template<typename T>
T* ToolBar::GetWorkspace() const
{
  return static_cast<T*>(mWorkspace);
}

} // End of Framework namespace
} // End of Editor namespace
