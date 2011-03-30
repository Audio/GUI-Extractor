#include "EButton.h"


EButton::EButton(IUIAutomationElement* element)
  : Element(element)
{
}

QString EButton::getType() const
{
  return "button";
}
