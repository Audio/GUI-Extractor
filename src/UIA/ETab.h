#ifndef ETAB_H
#define ETAB_H

#include "Element.h"


class ETab : public Element
{
public:
  ETab(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // ETAB_H
