#ifndef ESTATUSBAR_H
#define ESTATUSBAR_H

#include "Element.h"


class EStatusBar : public Element
{
public:
  EStatusBar(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // ESTATUSBAR_H
