#ifndef ELISTITEM_H
#define ELISTITEM_H

#include "Element.h"


class EListItem : public Element
{
public:
  EListItem(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int, int) const;
};

#endif // ELISTITEM_H
