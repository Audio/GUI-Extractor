#ifndef EMENUBAR_H
#define EMENUBAR_H

#include "Element.h"


class EMenuBar : public Element
{
public:
  EMenuBar(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL() const;
};

#endif // EMENUBAR_H
