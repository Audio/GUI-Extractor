#include "ECalendar.h"


ECalendar::ECalendar(IUIAutomationElement* element)
  : Element(element)
{
}

QString ECalendar::getType() const
{
  return "calendar";
}

XUL::Item* ECalendar::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("datepicker");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("type", "grid");
  return item;
}
