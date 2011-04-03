#include "EGroup.h"


EGroup::EGroup(IUIAutomationElement* element)
  : Element(element)
{
}

QString EGroup::getType() const
{
  return "group";
}
