#include "EToolTip.h"


EToolTip::EToolTip(IUIAutomationElement* element)
  : Element(element)
{
}

QString EToolTip::getType() const
{
  return "tooltip";
}
