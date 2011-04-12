#include "EText.h"


EText::EText(IUIAutomationElement* element)
  : Element(element)
{
}

QString EText::getType() const
{
  return "text";
}

XUL::Item* EText::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("label");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("value", getCachedName() );
  return item;
}
