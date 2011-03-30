#ifndef ESLIDER_H
#define ESLIDER_H

#include "Element.h"


class ESlider : public Element
{
public:
  ESlider(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ESLIDER_H
