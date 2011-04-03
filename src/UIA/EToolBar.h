#ifndef ETOOLBAR_H
#define ETOOLBAR_H

#include "Element.h"


class EToolBar : public Element
{
public:
  EToolBar(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ETOOLBAR_H
