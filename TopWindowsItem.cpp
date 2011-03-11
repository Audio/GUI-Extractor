#include "TopWindowsItem.h"


TopWindowsItem::TopWindowsItem(QListWidget* parent, Element* topWindow)
  : QListWidgetItem(parent)
{
  element = topWindow;
  setText( element->getName() );
}

TopWindowsItem::~TopWindowsItem()
{
  delete element;
}

Element* TopWindowsItem::getElement() const
{
  return element;
}
