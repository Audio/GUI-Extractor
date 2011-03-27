#ifndef ERADIO_H
#define ERADIO_H

#include "Element.h"


class ERadio : public Element
{
public:
  ERadio(IUIAutomationElement* element);
  QString getType();
};

#endif // ERADIO_H
