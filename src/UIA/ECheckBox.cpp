#include "ECheckBox.h"


ECheckBox::ECheckBox(IUIAutomationElement* element)
  : Element(element)
{
}

QString ECheckBox::getType()
{
  return "check box";
}
