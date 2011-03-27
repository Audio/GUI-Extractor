#ifndef EEDIT_H
#define EEDIT_H

#include "Element.h"


class EEdit : public Element
{
public:
  EEdit(IUIAutomationElement* element);
  QString getType();
};

#endif // EEDIT_H
