#ifndef ECALENDAR_H
#define ECALENDAR_H

#include "Element.h"


class ECalendar : public Element
{
public:
  ECalendar(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ECALENDAR_H
