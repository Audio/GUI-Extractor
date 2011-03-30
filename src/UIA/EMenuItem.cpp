#include "EMenuItem.h"


EMenuItem::EMenuItem(IUIAutomationElement* element)
  : Element(element)
{
}

QString EMenuItem::getType() const
{
  return "menu item";
}
