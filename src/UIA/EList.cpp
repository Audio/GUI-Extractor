#include "EList.h"


EList::EList(IUIAutomationElement* element)
  : Element(element)
{
}

QString EList::getType() const
{
  return "list";
}
