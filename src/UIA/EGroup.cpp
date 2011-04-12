#include "EGroup.h"


EGroup::EGroup(IUIAutomationElement* element)
  : Element(element)
{
}

QString EGroup::getType() const
{
  return "group";
}

XUL::Item* EGroup::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("groupbox");
  exportXULArea(item, diffLeft, diffTop);
  return item;
}
