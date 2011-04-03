#include "EDocument.h"


EDocument::EDocument(IUIAutomationElement* element)
  : Element(element)
{
}

QString EDocument::getType() const
{
  return "document";
}
