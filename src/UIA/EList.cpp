#include "EList.h"


EList::EList(IUIAutomationElement* element)
  : Element(element)
{
}

QString EList::getType() const
{
  return "list";
}

XUL::Item* EList::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("listbox");
  exportXULArea(item, diffLeft, diffTop);
  return item;
}
