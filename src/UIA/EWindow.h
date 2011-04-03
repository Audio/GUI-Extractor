#ifndef EWINDOW_H
#define EWINDOW_H

#include "Element.h"


class EWindow : public Element
{
public:
  EWindow(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EWINDOW_H
