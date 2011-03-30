#ifndef ESCROLLBAR_H
#define ESCROLLBAR_H

#include "Element.h"


class EScrollBar : public Element
{
public:
  EScrollBar(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ESCROLLBAR_H
