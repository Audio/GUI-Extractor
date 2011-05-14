#ifndef EHYPERLINK_H
#define EHYPERLINK_H

#include "Element.h"


class EHyperlink : public Element
{
public:
  EHyperlink(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int, int) const;
};

#endif // EHYPERLINK_H
