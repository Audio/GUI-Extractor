#include "EProgressBar.h"


EProgressBar::EProgressBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString EProgressBar::getType() const
{
  return "progress bar";
}

XUL::Item* EProgressBar::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("progressmeter");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("mode", "determined");
  item->setAttribute("value", "20");
  return item;
}
