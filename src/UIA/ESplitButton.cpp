#include "ESplitButton.h"


ESplitButton::ESplitButton(IUIAutomationElement* element)
  : Element(element)
{
}

QString ESplitButton::getType() const
{
  return "splitbutton";
}
