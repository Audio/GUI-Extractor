#ifndef ETOOLTIP_H
#define ETOOLTIP_H

#include "Element.h"


class EToolTip : public Element
{
public:
  EToolTip(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int, int) const;
};

#endif // ETOOLTIP_H
