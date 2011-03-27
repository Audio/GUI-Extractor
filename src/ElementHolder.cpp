#include "ElementHolder.h"


ElementHolder::ElementHolder(Element* element)
{
  this->element = element;
}

ElementHolder::~ElementHolder()
{
  delete element;
}

Element* ElementHolder::getElement() const
{
  return element;
}
