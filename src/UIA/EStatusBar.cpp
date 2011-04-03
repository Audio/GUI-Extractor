#include "EStatusBar.h"


EStatusBar::EStatusBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString EStatusBar::getType() const
{
  return "status bar";
}
