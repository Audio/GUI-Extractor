#include "EStatusBar.h"


EStatusBar::EStatusBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString EStatusBar::getType() const
{
  return "status bar";
}

XUL::Item* EStatusBar::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("statusbar");
  exportXULArea(item, diffLeft, diffTop);
  return item;
}
