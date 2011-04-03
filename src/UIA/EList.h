#ifndef ELIST_H
#define ELIST_H

#include "Element.h"


class EList : public Element
{
public:
  EList(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ELIST_H
