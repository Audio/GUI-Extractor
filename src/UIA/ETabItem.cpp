#include "ETabItem.h"


ETabItem::ETabItem(IUIAutomationElement* element)
  : Element(element)
{
}

QString ETabItem::getType() const
{
  return "tab item";
}

XUL::Item* ETabItem::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("tab");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("label", getCachedName() );
  return item;
}
