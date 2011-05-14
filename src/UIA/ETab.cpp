#include "ETab.h"


ETab::ETab(IUIAutomationElement* element)
  : Element(element)
{
}

QString ETab::getType() const
{
  return "tab";
}

XUL::Item* ETab::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("tabs");
  exportXULArea(item, diffLeft, diffTop);
  return item;
}
