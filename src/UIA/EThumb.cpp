#include "EThumb.h"


EThumb::EThumb(IUIAutomationElement* element)
  : Element(element)
{
}

QString EThumb::getType() const
{
  return "thumb";
}
