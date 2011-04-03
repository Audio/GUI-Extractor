#ifndef ELISTITEM_H
#define ELISTITEM_H

#include "Element.h"


class EListItem : public Element
{
public:
  EListItem(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ELISTITEM_H
