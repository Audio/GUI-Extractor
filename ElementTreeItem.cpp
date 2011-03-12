#include "ElementTreeItem.h"


ElementTreeItem::ElementTreeItem(QTreeWidget* parent, Element* element)
  : QTreeWidgetItem(parent)
{
  initialize(element);
}

ElementTreeItem::ElementTreeItem(ElementTreeItem* parent, Element* element)
  : QTreeWidgetItem(parent)
{
  initialize(element);
}

ElementTreeItem::~ElementTreeItem()
{
  delete element;
}

Element* ElementTreeItem::getElement() const
{
  return element;
}

void ElementTreeItem::initialize(Element* element)
{
  this->element = element;
  setText(0, element->getName() );
}
