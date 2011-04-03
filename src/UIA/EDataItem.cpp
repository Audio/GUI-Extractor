#include "EDataItem.h"


EDataItem::EDataItem(IUIAutomationElement* element)
  : Element(element)
{
}

QString EDataItem::getType() const
{
  return "data item";
}
