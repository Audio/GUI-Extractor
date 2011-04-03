#ifndef EIMAGE_H
#define EIMAGE_H

#include "Element.h"


class EImage : public Element
{
public:
  EImage(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EIMAGE_H
