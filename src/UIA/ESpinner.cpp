#include "ESpinner.h"


ESpinner::ESpinner(IUIAutomationElement* element)
  : Element(element)
{
}

QString ESpinner::getType() const
{
  return "spinner";
}
