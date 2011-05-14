#include "EListItem.h"


EListItem::EListItem(IUIAutomationElement* element)
  : Element(element)
{
}

QString EListItem::getType() const
{
  return "list item";
}

XUL::Item* EListItem::exportXUL(int, int) const
{
  XUL::Item* item = new XUL::Item("listitem");
  item->setAttribute("label", getCachedName() );
  return item;
}
