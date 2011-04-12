#ifndef ERADIO_H
#define ERADIO_H

#include "Element.h"


class ERadio : public Element
{
public:
  ERadio(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // ERADIO_H
