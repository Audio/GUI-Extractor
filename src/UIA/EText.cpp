#include "EText.h"


EText::EText(IUIAutomationElement* element)
  : Element(element)
{
}

QString EText::getType() const
{
  return "text";
}
