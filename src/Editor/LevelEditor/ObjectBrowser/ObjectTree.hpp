#pragma once

#include <qtreewidget.h>

namespace Editor
{

class ObjectBrowser;

class ObjectTree : public QTreeWidget
{
public:
  ObjectTree(ObjectBrowser* objectBrowser);

private:
  ObjectBrowser* mObjectBrowser;

};

} // End of Editor namespace
