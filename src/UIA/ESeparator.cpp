#include "ESeparator.h"


ESeparator::ESeparator(IUIAutomationElement* element)
  : Element(element)
{
}

QString ESeparator::getType() const
{
  return "separator";
}
