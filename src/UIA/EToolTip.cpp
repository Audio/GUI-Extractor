#include "EToolTip.h"


EToolTip::EToolTip(IUIAutomationElement* element)
  : Element(element)
{
}

QString EToolTip::getType() const
{
  return "tooltip";
}

XUL::Item* EToolTip::exportXUL(int, int) const
{
  return XUL::NO_EXPORT;
}
