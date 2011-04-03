#ifndef ETABLE_H
#define ETABLE_H

#include "Element.h"


class ETable : public Element
{
public:
  ETable(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ETABLE_H
