#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtCore/QString>
#include "includes.h"
#include "ElementArea.h"
#include "XUL/Item.h"


class ElementFactory;

class Element
{
  friend class ElementFactory;

protected:
  Element(IUIAutomationElement* element);

public:
  ~Element();

  const ElementArea* getArea() const;
  QString getName();
  IUIAutomationElement* getUIAElement() const;
  virtual QString getType() = 0;
  virtual XUL::Item* exportXUL() const;

private:
  void exportXULArea(XUL::Item* item) const;

  QString bstrToQString(BSTR& bstr);

  IUIAutomationElement* UIAElement;
  QString cachedName;
};

#endif // ELEMENT_H
