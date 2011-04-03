#ifndef ETOOLTIP_H
#define ETOOLTIP_H

#include "Element.h"


class EToolTip : public Element
{
public:
  EToolTip(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ETOOLTIP_H
