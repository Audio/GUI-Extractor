#ifndef ETABITEM_H
#define ETABITEM_H

#include "Element.h"


class ETabItem : public Element
{
public:
  ETabItem(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // ETABITEM_H
