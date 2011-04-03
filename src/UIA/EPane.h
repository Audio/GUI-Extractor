#ifndef EPANE_H
#define EPANE_H

#include "Element.h"


class EPane : public Element
{
public:
  EPane(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EPANE_H
