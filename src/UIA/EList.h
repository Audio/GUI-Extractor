#ifndef ELIST_H
#define ELIST_H

#include "Element.h"


class EList : public Element
{
public:
  EList(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // ELIST_H
