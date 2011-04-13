#include "ESeparator.h"


ESeparator::ESeparator(IUIAutomationElement* element)
  : Element(element)
{
}

QString ESeparator::getType() const
{
  return "separator";
}

XUL::Item* ESeparator::exportXUL(int, int) const
{
  XUL::Item* item = new XUL::Item("menuseparator");
  return item;
}
