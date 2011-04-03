#include "EMenu.h"


EMenu::EMenu(IUIAutomationElement* element)
  : Element(element)
{
}

QString EMenu::getType() const
{
  return "menu";
}
