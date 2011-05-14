#include "EThumb.h"


EThumb::EThumb(IUIAutomationElement* element)
  : Element(element)
{
}

QString EThumb::getType() const
{
  return "thumb";
}

XUL::Item* EThumb::exportXUL(int, int) const
{
  return XUL::NO_EXPORT;
}
