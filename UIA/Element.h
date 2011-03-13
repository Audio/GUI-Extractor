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

  const ElementArea* getArea() const;
  QString getName();
  IUIAutomationElement* getUIAElement() const;

private:
  QString bstrToQString(BSTR& bstr);

  IUIAutomationElement* UIAElement;
  QString cachedName;
};

#endif // ELEMENT_H
