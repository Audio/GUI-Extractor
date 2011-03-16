#ifndef ECHECKBOX_H
#define ECHECKBOX_H

#include "Element.h"


class ECheckBox : public Element
{
public:
  ECheckBox(IUIAutomationElement* element);
  QString getType();
};

#endif // ECHECKBOX_H
