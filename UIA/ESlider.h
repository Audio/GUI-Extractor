#ifndef ESLIDER_H
#define ESLIDER_H

#include "Element.h"


class ESlider : public Element
{
public:
  ESlider(IUIAutomationElement* element);
  QString getType();
};

#endif // ESLIDER_H
