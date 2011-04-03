#include "ETitleBar.h"


ETitleBar::ETitleBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString ETitleBar::getType() const
{
  return "titlebar";
}
