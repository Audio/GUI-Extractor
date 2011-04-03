#include "EImage.h"


EImage::EImage(IUIAutomationElement* element)
  : Element(element)
{
}

QString EImage::getType() const
{
  return "image";
}
