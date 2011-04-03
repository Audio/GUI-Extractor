#include "EHeaderItem.h"


EHeaderItem::EHeaderItem(IUIAutomationElement* element)
  : Element(element)
{
}

QString EHeaderItem::getType() const
{
  return "header item";
}
