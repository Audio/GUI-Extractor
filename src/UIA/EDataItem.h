#ifndef EDATAITEM_H
#define EDATAITEM_H

#include "Element.h"


class EDataItem : public Element
{
public:
  EDataItem(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EDATAITEM_H
