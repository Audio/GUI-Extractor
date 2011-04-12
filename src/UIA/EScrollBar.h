#ifndef ESCROLLBAR_H
#define ESCROLLBAR_H

#include "Element.h"


class EScrollBar : public Element
{
public:
  EScrollBar(IUIAutomationElement* element);
  inline bool ignoreChildren() const { return true; };
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // ESCROLLBAR_H
