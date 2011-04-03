#ifndef ETITLEBAR_H
#define ETITLEBAR_H

#include "Element.h"


class ETitleBar : public Element
{
public:
  ETitleBar(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ETITLEBAR_H
