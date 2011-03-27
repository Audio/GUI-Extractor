#ifndef EMENUITEM_H
#define EMENUITEM_H

#include "Element.h"


class EMenuItem : public Element
{
public:
  EMenuItem(IUIAutomationElement* element);
  QString getType();
};

#endif // EMENUITEM_H
