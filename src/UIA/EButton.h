#ifndef EBUTTON_H
#define EBUTTON_H

#include "Element.h"


class EButton : public Element
{
public:
  EButton(IUIAutomationElement* element);
  QString getType();
};

#endif // EBUTTON_H
