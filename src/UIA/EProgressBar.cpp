#include "EProgressBar.h"


EProgressBar::EProgressBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString EProgressBar::getType() const
{
  return "progress bar";
}
