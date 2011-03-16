#ifndef ELEMENTFACTORY_H
#define ELEMENTFACTORY_H

#include "Element.h"
#include "includes.h"


class ElementFactory
{
public:
    static Element* getElement(IUIAutomationElement* element);
};

#endif // ELEMENTFACTORY_H
