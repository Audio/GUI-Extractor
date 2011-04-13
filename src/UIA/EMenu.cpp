#include "EMenu.h"


EMenu::EMenu(IUIAutomationElement* element)
  : Element(element)
{
}

QString EMenu::getType() const
{
  return "menu";
}

XUL::Item* EMenu::exportXUL(int, int) const
{
  XUL::Item* item = new XUL::Item("menu");
  item->setAttribute("label", getCachedName() );
  return item;
}
