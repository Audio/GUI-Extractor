#ifndef ECOMBOBOX_H
#define ECOMBOBOX_H

#include "Element.h"


class EComboBox : public Element
{
public:
  EComboBox(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // ECOMBOBOX_H
