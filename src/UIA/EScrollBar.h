#ifndef ESCROLLBAR_H
#define ESCROLLBAR_H

#include "Element.h"


class EScrollBar : public Element
{
public:
  EScrollBar(IUIAutomationElement* element);
  QString getType();
};

#endif // ESCROLLBAR_H
