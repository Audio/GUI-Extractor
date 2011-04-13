#ifndef EMENU_H
#define EMENU_H

#include "Element.h"


class EMenu : public Element
{
public:
  EMenu(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int, int) const;
};

#endif // EMENU_H
