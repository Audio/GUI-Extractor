#ifndef EHYPERLINK_H
#define EHYPERLINK_H

#include "Element.h"


class EHyperlink : public Element
{
public:
  EHyperlink(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EHYPERLINK_H
