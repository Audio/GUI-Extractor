#include "EMenuItem.h"


EMenuItem::EMenuItem(IUIAutomationElement* element)
  : Element(element)
{
}

QString EMenuItem::getType()
{
  return "menu item";
}
