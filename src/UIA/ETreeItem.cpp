#include "ETreeItem.h"


ETreeItem::ETreeItem(IUIAutomationElement* element)
  : Element(element)
{
}

QString ETreeItem::getType() const
{
  return "tree item";
}
