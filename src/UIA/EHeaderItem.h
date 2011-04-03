#ifndef EHEADERITEM_H
#define EHEADERITEM_H

#include "Element.h"


class EHeaderItem : public Element
{
public:
  EHeaderItem(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EHEADERITEM_H
