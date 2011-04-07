#include "Element.h"
#include <QtCore/QDebug>


Element::Element(IUIAutomationElement* element)
{
  UIAElement = element;
  qDebug() << "Created element " + getName();
}

Element::~Element()
{
  UIAElement->Release();
  qDebug() << "Memory for object " + cachedName + " released.";
}

ElementArea Element::getArea(bool& valid) const
{
  RECT rect;
  HRESULT hr = UIAElement->get_CurrentBoundingRectangle(&rect);
  valid = SUCCEEDED(hr);
  return ElementArea(rect);
}

bool Element::isOffScreen() const
{
  BOOL offScreen;
  HRESULT hr = UIAElement->get_CurrentIsOffscreen(&offScreen);
  return SUCCEEDED(hr) && offScreen;
}

QString Element::getCachedName() const
{
  return cachedName;
}

QString Element::getName()
{
  if ( cachedName.isEmpty() ) {
    BSTR name;
    HRESULT hr = UIAElement->get_CurrentName(&name);
    if ( SUCCEEDED(hr) && name )
      cachedName = bstrToQString(name);
  }

  return cachedName;
}

IUIAutomationElement* Element::getUIAElement() const
{
  return UIAElement;
}

XUL::Item* Element::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("stack");
  exportXULArea(item, diffLeft, diffTop);
  return item;
}

void Element::exportXULArea(XUL::Item* item, int diffLeft, int diffTop) const
{
  bool valid;
  ElementArea a = getArea(valid);
  if (valid) {
    item->setAttribute("top", QString::number( a.getTop() - diffTop ));
    item->setAttribute("left", QString::number( a.getLeft() - diffLeft ));
    item->setAttribute("width", QString::number( a.getWidth() ));
    item->setAttribute("height", QString::number( a.getHeight() ));
  }
}

QString Element::bstrToQString(BSTR& bstr)
{
  std::wstring str = (LPCWSTR) bstr;
  QString qstr = QString::fromStdWString(str);
  SysFreeString(bstr);
  return qstr;
}
