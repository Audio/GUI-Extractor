#include "ETabItem.h"


ETabItem::ETabItem(IUIAutomationElement* element)
  : Element(element)
{
}

QString ETabItem::getType() const
{
  return "tab item";
}
