#include "ESeparator.h"


ESeparator::ESeparator(IUIAutomationElement* element)
  : Element(element)
{
}

QString ESeparator::getType() const
{
  return "separator";
}

XUL::Item* ESeparator::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("separator");
  exportXULArea(item, diffLeft, diffTop);
  return item;
}
