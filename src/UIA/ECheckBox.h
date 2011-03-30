#ifndef ECHECKBOX_H
#define ECHECKBOX_H

#include "Element.h"


class ECheckBox : public Element
{
public:
  ECheckBox(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ECHECKBOX_H
