#ifndef ETHUMB_H
#define ETHUMB_H

#include "Element.h"


class EThumb : public Element
{
public:
  EThumb(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int, int) const;
};

#endif // ETHUMB_H
