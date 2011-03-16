#include "ElementFactory.h"


Element* ElementFactory::getElement(IUIAutomationElement* element)
{
  // TODO: Temporary, only the parent class is available
  return new Element(element);
}
