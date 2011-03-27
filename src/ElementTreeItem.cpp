#include "ElementTreeItem.h"


ElementTreeItem::ElementTreeItem(QTreeWidget* parent, Element* element)
  : ElementHolder(element), QTreeWidgetItem(parent)
{
  setDescription();
}

ElementTreeItem::ElementTreeItem(ElementTreeItem* parent, Element* element)
  : ElementHolder(element), QTreeWidgetItem(parent)
{
  setDescription();
}

void ElementTreeItem::setDescription()
{
  QString name = element->getName().isEmpty() ? "-" : element->getName();

  setText(0, name);
  setText(1, element->getType() );
}
