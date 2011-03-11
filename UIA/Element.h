#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtCore/QString>
#include "includes.h"


class Element
{
public:
  Element(IUIAutomationElement* element);
  ~Element();

  QString getName();

private:
  QString bstrToQString(const BSTR& bstr);

  IUIAutomationElement* UIAElement;
};

#endif // ELEMENT_H
