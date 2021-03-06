#ifndef EGROUP_H
#define EGROUP_H

#include "Element.h"


class EGroup : public Element
{
public:
  EGroup(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // EGROUP_H
