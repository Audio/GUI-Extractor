#include "ESpinner.h"


ESpinner::ESpinner(IUIAutomationElement* element)
  : Element(element)
{
}

QString ESpinner::getType() const
{
  return "spinner";
}

XUL::Item* ESpinner::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("spinner");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("min", "0");
  item->setAttribute("min", "5");
  item->setAttribute("value", "0");
  return item;
}
