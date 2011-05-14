#ifndef ESPINNER_H
#define ESPINNER_H

#include "Element.h"


class ESpinner : public Element
{
public:
  ESpinner(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // ESPINNER_H
