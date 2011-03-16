#include "EUnknown.h"


EUnknown::EUnknown(IUIAutomationElement* element)
  : Element(element)
{
}

QString EUnknown::getType()
{
  return "unknown";
}
