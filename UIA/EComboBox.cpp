#include "EComboBox.h"


EComboBox::EComboBox(IUIAutomationElement* element)
  : Element(element)
{
}

QString EComboBox::getType()
{
  return "combo box";
}
