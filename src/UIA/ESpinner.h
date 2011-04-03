#ifndef ESPINNER_H
#define ESPINNER_H

#include "Element.h"


class ESpinner : public Element
{
public:
  ESpinner(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ESPINNER_H
