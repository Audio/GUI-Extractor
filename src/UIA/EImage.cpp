#include "EImage.h"


EImage::EImage(IUIAutomationElement* element)
  : Element(element)
{
}

QString EImage::getType() const
{
  return "image";
}

XUL::Item* EImage::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("spacer");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("flex", "0");
  item->setAttribute("class", "image");
  return item;
}
