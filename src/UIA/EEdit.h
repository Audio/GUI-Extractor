#ifndef EEDIT_H
#define EEDIT_H

#include "Element.h"


class EEdit : public Element
{
public:
  EEdit(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EEDIT_H
