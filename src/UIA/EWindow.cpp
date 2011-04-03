#include "EWindow.h"


EWindow::EWindow(IUIAutomationElement* element)
  : Element(element)
{
}

QString EWindow::getType() const
{
  return "window";
}
