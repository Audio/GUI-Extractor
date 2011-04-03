#ifndef EDOCUMENT_H
#define EDOCUMENT_H

#include "Element.h"


class EDocument : public Element
{
public:
  EDocument(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EDOCUMENT_H
