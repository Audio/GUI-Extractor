#ifndef EMENUBAR_H
#define EMENUBAR_H

#include "Element.h"


class EMenuBar : public Element
{
public:
  EMenuBar(IUIAutomationElement* element);
  QString getType();
};

#endif // EMENUBAR_H
