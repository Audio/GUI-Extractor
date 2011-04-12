#include "ERadio.h"


ERadio::ERadio(IUIAutomationElement* element)
  : Element(element)
{
}

QString ERadio::getType() const
{
  return "radio";
}

XUL::Item* ERadio::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("radio");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("label", getCachedName() );
  return item;
}
