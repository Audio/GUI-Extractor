#include "EToolBar.h"


EToolBar::EToolBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString EToolBar::getType() const
{
  return "toolbar";
}

XUL::Item* EToolBar::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("toolbar");
  exportXULArea(item, diffLeft, diffTop);
  return item;
}
