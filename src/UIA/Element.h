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

  ElementArea getArea(bool& valid) const;
  bool isOffScreen() const;
  QString getCachedName() const;
  QString getName();
  QString getLocalizedType();
  QString getOrientation() const;
  IUIAutomationElement* getUIAElement() const;
  virtual inline bool ignoreChildren() const { return false; };
  virtual inline QString getType() const = 0;
  virtual XUL::Item* exportXUL(int diffLeft, int diffTop) const;

protected:
  void exportXULArea(XUL::Item* item, int diffLeft, int diffTop, bool noDiff = false) const;

  QString bstrToQString(BSTR& bstr);

  IUIAutomationElement* UIAElement;
  QString cachedName;
};

#endif // ELEMENT_H
