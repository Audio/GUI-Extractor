#ifndef ETAB_H
#define ETAB_H

#include "Element.h"


class ETab : public Element
{
public:
  ETab(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ETAB_H
