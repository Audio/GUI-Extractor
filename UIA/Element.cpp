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

const ElementArea* Element::getArea() const
{
  RECT rect;
  HRESULT hr = UIAElement->get_CurrentBoundingRectangle(&rect);
  return SUCCEEDED(hr) ? new ElementArea(rect) : NULL;
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

QString Element::bstrToQString(BSTR& bstr)
{
  std::wstring str = (LPCWSTR) bstr;
  QString qstr = QString::fromStdWString(str);
  SysFreeString(bstr);
  return qstr;
}
