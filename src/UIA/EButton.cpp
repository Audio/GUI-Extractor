#include "EButton.h"


EButton::EButton(IUIAutomationElement* element)
  : Element(element)
{
}

QString EButton::getType() const
{
  return "button";
}

XUL::Item* EButton::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("button");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("style", "min-width:0");
  item->setAttribute("label", getCachedName() );
  return item;
}
