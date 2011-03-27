#ifndef ELEMENTHOLDER_H
#define ELEMENTHOLDER_H

#include "UIA/Element.h"


class ElementHolder
{
public:
  ElementHolder(Element* element);
  ~ElementHolder();

  Element* getElement() const;

protected:
  Element* element;
};

#endif // ELEMENTHOLDER_H
