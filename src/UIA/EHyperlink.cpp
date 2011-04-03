#include "EHyperlink.h"


EHyperlink::EHyperlink(IUIAutomationElement* element)
  : Element(element)
{
}

QString EHyperlink::getType() const
{
  return "hyperlink";
}
