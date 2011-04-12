#include "ESlider.h"


ESlider::ESlider(IUIAutomationElement* element)
  : Element(element)
{
}

QString ESlider::getType() const
{
  return "slider";
}

XUL::Item* ESlider::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("slider");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("orient", getOrientation() );
  return item;
}
