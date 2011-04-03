#ifndef ETABITEM_H
#define ETABITEM_H

#include "Element.h"


class ETabItem : public Element
{
public:
  ETabItem(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ETABITEM_H
