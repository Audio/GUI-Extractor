#ifndef ETOOLBAR_H
#define ETOOLBAR_H

#include "Element.h"


class EToolBar : public Element
{
public:
  EToolBar(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // ETOOLBAR_H
