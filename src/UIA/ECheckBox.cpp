#include "ECheckBox.h"


ECheckBox::ECheckBox(IUIAutomationElement* element)
  : Element(element)
{
}

QString ECheckBox::getType() const
{
  return "check box";
}

XUL::Item* ECheckBox::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("checkbox");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("label", getCachedName() );
  item->setAttribute("checked", "false");
  return item;
}
