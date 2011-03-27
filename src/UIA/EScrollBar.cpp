#include "EScrollBar.h"


EScrollBar::EScrollBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString EScrollBar::getType()
{
  return "scrollbar";
}
