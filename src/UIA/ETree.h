#ifndef ETREE_H
#define ETREE_H

#include "Element.h"


class ETree : public Element
{
public:
  ETree(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ETREE_H
