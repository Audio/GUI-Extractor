#include "EScrollBar.h"


EScrollBar::EScrollBar(IUIAutomationElement* element)
  : Element(element)
{
}

QString EScrollBar::getType() const
{
  return "scrollbar";
}

XUL::Item* EScrollBar::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("scrollbar");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("orient", getOrientation() );
  return item;
}
