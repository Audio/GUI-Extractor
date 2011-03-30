#include "ECheckBox.h"


ECheckBox::ECheckBox(IUIAutomationElement* element)
  : Element(element)
{
}

QString ECheckBox::getType() const
{
  return "check box";
}
