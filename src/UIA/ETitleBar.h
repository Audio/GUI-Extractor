#ifndef ETITLEBAR_H
#define ETITLEBAR_H

#include "Element.h"


class ETitleBar : public Element
{
public:
  ETitleBar(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int, int) const;
};

#endif // ETITLEBAR_H
