#ifndef EUnknown_H
#define EUnknown_H

#include "Element.h"


class EUnknown : public Element
{
public:
  EUnknown(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EUnknown_H
