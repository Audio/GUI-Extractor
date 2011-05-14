#ifndef ESPLITBUTTON_H
#define ESPLITBUTTON_H

#include "Element.h"


class ESplitButton : public Element
{
public:
  ESplitButton(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int, int) const;
};

#endif // ESPLITBUTTON_H
