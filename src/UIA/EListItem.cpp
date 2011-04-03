#include "EListItem.h"


EListItem::EListItem(IUIAutomationElement* element)
  : Element(element)
{
}

QString EListItem::getType() const
{
  return "list item";
}
