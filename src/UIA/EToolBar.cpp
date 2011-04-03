#include "EToolBar.h"


EToolBar::EToolBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString EToolBar::getType() const
{
  return "toolbar";
}
