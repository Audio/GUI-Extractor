#ifndef EHEADER_H
#define EHEADER_H

#include "Element.h"


class EHeader : public Element
{
public:
  EHeader(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EHEADER_H
