#include "Element.h"
#include <QtCore/QDebug>


Element::Element(IUIAutomationElement* element)
  : area(NULL)
{
  UIAElement = element;
  qDebug() << "Created element " + getName();
}

Element::~Element()
{
  if (area)
    delete area;

  qDebug() << "Memory for object " + getName() + " released.";
  UIAElement->Release();
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

ElementArea* Element::getArea()
{
  if (!area) {
    RECT rect;
    HRESULT hr = UIAElement->get_CurrentBoundingRectangle(&rect);
    if ( SUCCEEDED(hr) )
      area = new ElementArea(rect);
  }

  return area;
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
