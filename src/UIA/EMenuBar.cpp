#include "EMenuBar.h"


EMenuBar::EMenuBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString EMenuBar::getType()
{
  return "menubar";
}
