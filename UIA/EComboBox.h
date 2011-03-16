#ifndef ECOMBOBOX_H
#define ECOMBOBOX_H

#include "Element.h"


class EComboBox : public Element
{
public:
  EComboBox(IUIAutomationElement* element);
  QString getType();
};

#endif // ECOMBOBOX_H
