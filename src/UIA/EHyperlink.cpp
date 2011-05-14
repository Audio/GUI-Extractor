#include "EHyperlink.h"


EHyperlink::EHyperlink(IUIAutomationElement* element)
  : Element(element)
{
}

QString EHyperlink::getType() const
{
  return "hyperlink";
}

XUL::Item* EHyperlink::exportXUL(int, int) const
{
  return XUL::NO_EXPORT;
}
