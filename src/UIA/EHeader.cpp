#include "EHeader.h"


EHeader::EHeader(IUIAutomationElement* element)
  : Element(element)
{
}

QString EHeader::getType() const
{
  return "header";
}
