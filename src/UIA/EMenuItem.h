#ifndef EMENUITEM_H
#define EMENUITEM_H

#include "Element.h"


class EMenuItem : public Element
{
public:
  EMenuItem(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EMENUITEM_H
