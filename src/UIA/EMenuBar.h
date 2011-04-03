#ifndef EMENUBAR_H
#define EMENUBAR_H

#include "Element.h"


class EMenuBar : public Element
{
public:
  EMenuBar(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // EMENUBAR_H
