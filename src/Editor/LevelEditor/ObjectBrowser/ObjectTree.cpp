#include "Editor/LevelEditor/ObjectBrowser/ObjectTree.hpp"

namespace Editor
{

ObjectTree::ObjectTree(ObjectBrowser* objectBrowser)
: QTreeWidget()
, mObjectBrowser(objectBrowser)
{
  setHeaderLabel("Object Browser");

  QTreeWidgetItem* item = new QTreeWidgetItem(this);
  item->setText(0, "Test Item");
  addTopLevelItem(item);
}

} // End of Editor namespace

