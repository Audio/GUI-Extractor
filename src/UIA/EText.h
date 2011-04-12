#ifndef ETEXT_H
#define ETEXT_H

#include "Element.h"


class EText : public Element
{
public:
  EText(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // ETEXT_H
