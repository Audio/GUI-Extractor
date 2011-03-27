#include "TopWindowsItem.h"


TopWindowsItem::TopWindowsItem(QTreeWidget* parent, Element* topWindow)
  : ElementHolder(topWindow), QTreeWidgetItem(parent)
{
  setText(0, element->getName() );
}
