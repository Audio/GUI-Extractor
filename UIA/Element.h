#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtCore/QString>
#include "includes.h"
#include "ElementArea.h"


class Element
{
public:
  Element(IUIAutomationElement* element);
  ~Element();

  QString getName();
  ElementArea* getArea();
  IUIAutomationElement* getUIAElement() const;

private:
  QString bstrToQString(BSTR& bstr);

  IUIAutomationElement* UIAElement;
  ElementArea* area;
  QString cachedName;
};

#endif // ELEMENT_H
