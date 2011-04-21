#include "TopWindowsItem.h"


TopWindowsItem::TopWindowsItem(QTreeWidget* parent, Element* topWindow)
  : ElementHolder(topWindow), QTreeWidgetItem(parent)
{
  QString text = element->getName();
  if ( text.isEmpty() )
    text = " ?? [" + element->getLocalizedType() + "]";

  setText(0, text);
}
