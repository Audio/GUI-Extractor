#include "EPane.h"


EPane::EPane(IUIAutomationElement* element)
  : Element(element)
{
}

QString EPane::getType() const
{
  return "panel";
}
