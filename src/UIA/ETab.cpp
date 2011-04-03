#include "ETab.h"


ETab::ETab(IUIAutomationElement* element)
  : Element(element)
{
}

QString ETab::getType() const
{
  return "tab";
}
