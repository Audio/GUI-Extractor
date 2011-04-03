#include "ECalendar.h"


ECalendar::ECalendar(IUIAutomationElement* element)
  : Element(element)
{
}

QString ECalendar::getType() const
{
  return "calendar";
}
