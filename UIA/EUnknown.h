#ifndef EUnknown_H
#define EUnknown_H

#include "Element.h"


class EUnknown : public Element
{
public:
    EUnknown(IUIAutomationElement* element);
    QString getType();
};

#endif // EUnknown_H
