#include "ERadio.h"


ERadio::ERadio(IUIAutomationElement* element)
  : Element(element)
{
}

QString ERadio::getType()
{
  return "radio";
}
