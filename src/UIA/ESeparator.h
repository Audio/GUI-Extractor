#ifndef ESEPARATOR_H
#define ESEPARATOR_H

#include "Element.h"


class ESeparator : public Element
{
public:
  ESeparator(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int, int) const;
};

#endif // ESEPARATOR_H
