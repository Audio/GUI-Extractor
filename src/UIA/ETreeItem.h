#ifndef ETREEITEM_H
#define ETREEITEM_H

#include "Element.h"


class ETreeItem : public Element
{
public:
  ETreeItem(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ETREEITEM_H
