#ifndef ESTATUSBAR_H
#define ESTATUSBAR_H

#include "Element.h"


class EStatusBar : public Element
{
public:
  EStatusBar(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ESTATUSBAR_H
