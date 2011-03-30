#include "EMenuBar.h"


EMenuBar::EMenuBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString EMenuBar::getType() const
{
  return "menubar";
}

XUL::Item* EMenuBar::exportXUL() const
{
  XUL::Item* item = new XUL::Item("menubar");
  exportXULArea(item);
  return item;
}
