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
  IUIAutomationElement* getUIAElement() const;
  void highlight();

private:
  void destroyActiveArea();
  QString bstrToQString(BSTR& bstr);

  IUIAutomationElement* UIAElement;
  ElementArea* area;
  QString cachedName;
};

#endif // ELEMENT_H
