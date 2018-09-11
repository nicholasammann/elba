#pragma once

#include "Elba/Utilities/StdTypedefs.hpp"

#include "Editor/Framework/Widget.hpp"

#include "Editor/LevelEditor/ObjectBrowser/ObjectTree.hpp"

namespace Editor
{

class ObjectBrowser : public Framework::Widget
{
public:
  ObjectBrowser(Framework::Workspace* workspace);

  Framework::Widget::DockArea GetDefaultDockArea() const final;
  Framework::Widget::DockArea GetAllowedDockAreas() const final;

private:
  Elba::UniquePtr<ObjectTree> mObjectTree;

};

} // End of Editor namespace