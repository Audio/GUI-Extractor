#include "ESplitButton.h"


ESplitButton::ESplitButton(IUIAutomationElement* element)
  : Element(element)
{
}

QString ESplitButton::getType() const
{
  return "splitbutton";
}

XUL::Item* ESplitButton::exportXUL(int, int) const
{
  return XUL::NO_EXPORT;
}
