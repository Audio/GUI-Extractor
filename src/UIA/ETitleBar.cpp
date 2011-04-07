#include "ETitleBar.h"


ETitleBar::ETitleBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString ETitleBar::getType() const
{
  return "titlebar";
}

XUL::Item* ETitleBar::exportXUL(int, int) const
{
  return XUL::NO_EXPORT;
}
